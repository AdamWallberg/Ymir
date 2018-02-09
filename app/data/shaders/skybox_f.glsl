#version 330 core

uniform samplerCube uSkybox;

in vec3 vTexCoords;

out vec4 fColor;

void main()
{
	fColor = texture(uSkybox, vTexCoords);
	gl_FragDepth = 1.0;
}