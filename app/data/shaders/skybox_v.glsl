#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view_mat;
uniform mat4 proj_mat;

out vec3 vTexCoords;

void main()
{
	vTexCoords = aPos;
	gl_Position = proj_mat * view_mat * vec4(aPos, 1.0);
}