#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;
layout (location = 3) out uint gID;

struct Material
{
	sampler2D texture_diffuse;
	bool texture_diffuse_bound;
	sampler2D texture_specular;
	bool texture_specular_bound;
	sampler2D texture_normal;
	bool texture_normal_bound;
	sampler2D texture_reflection;
	bool texture_reflection_bound;
	sampler2D texture_displacement;
	bool texture_displacement_bound;
	float shininess;
};

uniform Material material;

in VS_OUT
{
	vec2 uv;
	vec3 fragPos;
	mat3 TBN;
	vec3 normal;
	flat uint id;
	float selected;
} fs_in;

void main()
{
	// Output position
	gPosition = fs_in.fragPos;
	
	// Output normals
	gNormal = texture(material.texture_normal, fs_in.uv).rgb;
	gNormal = normalize(gNormal * 2.0 - 1.0);
	gNormal = normalize(fs_in.TBN * gNormal);
	gNormal = gNormal * 0.5 + 0.5;
	//gNormal = normalize(fs_in.normal);

	// Output color
	if(material.texture_diffuse_bound)
		gAlbedoSpec.rgb = texture(material.texture_diffuse, fs_in.uv).rgb;
	else
		gAlbedoSpec.rgb = vec3(1.0, 1.0, 1.0);

	// Output specular
	if(material.texture_specular_bound)
		gAlbedoSpec.a = texture(material.texture_specular, fs_in.uv).r;
	else
		gAlbedoSpec.a = 1.0;
		
	if(fs_in.selected > 0.5)
	{
		gAlbedoSpec.rgb = vec3(1.0, 1.0, 0.0);
	}
		
	gID = fs_in.id;
}




