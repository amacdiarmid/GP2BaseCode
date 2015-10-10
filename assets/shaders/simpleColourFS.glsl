#version 150

in vec4 vertexColourOut;

out vec4 FragColour;

void main()
{
	FragColour = vertexColourOut;
}