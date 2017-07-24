#version 330 core

uniform sampler2D uTexture;

in vec2 vTexCoords;

out vec4 fColor;

void main()
{
	fColor = texture(uTexture, vTexCoords);
}