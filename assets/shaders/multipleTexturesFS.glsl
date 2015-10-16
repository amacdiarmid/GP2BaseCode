#version 150

in vec4 vertexColourOut;
in vec2 vertexTexCoordsOut;

uniform sampler2D texture0;
uniform sampler2D texture1;

out vec4 FragColour;

void main()
{
	FragColour = texture(texture0, vertexTexCoordsOut) * texture(texture1, vertexTexCoordsOut);
}