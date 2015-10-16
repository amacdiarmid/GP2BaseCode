#version 150

in vec4 vertexColourOut;
in vec2 vertexTexCoordsOut;

uniform sampler2D texture0;
uniform vec4 uniColour;

out vec4 FragColour;

void main()
{
	FragColour = texture(texture0, vertexTexCoordsOut) * uniColour;
}