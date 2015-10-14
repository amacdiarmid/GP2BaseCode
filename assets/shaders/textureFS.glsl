#version 150

in vec4 vertexColourOut;
in vec2 vertexTexCoordsOut;

uniform sampler2D texture0;

out vec4 FragColour;

void main()
{
	FragColour = texture(texture0, vertexTexCoordsOut);
}