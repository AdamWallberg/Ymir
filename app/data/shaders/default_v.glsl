#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in mat4 aInstanceMatrix;
layout (location = 9) in uint aID;
layout (location = 10) in float aSelected;

uniform mat4 view_mat;
uniform mat4 proj_mat;

out VS_OUT
{
	vec2 uv;
	vec3 fragPos;
	mat3 TBN;
	vec3 normal;
	flat uint id;
	float selected;
} vs_out;

void main()
{
	vec4 worldPos = aInstanceMatrix * vec4(aPos, 1.0);
	vec4 viewPos = view_mat * worldPos;
	vs_out.fragPos = viewPos.xyz;
	vs_out.uv = aUV;

	vec3 T = normalize(vec3(aInstanceMatrix * vec4(aTangent, 0.0)));
	vec3 B = normalize(vec3(aInstanceMatrix * vec4(aBitangent, 0.0)));
	vec3 N = normalize(vec3(aInstanceMatrix * vec4(aNormal, 0.0)));
	mat3 TBN = mat3(T, B, N);
	vs_out.TBN = TBN;

	mat3 normalMatrix = transpose(inverse(mat3(view_mat * aInstanceMatrix)));
	vs_out.normal = normalMatrix * aNormal;
	
	vs_out.id = aID;
	vs_out.selected = aSelected;
	
	gl_Position = proj_mat * view_mat * worldPos;
}