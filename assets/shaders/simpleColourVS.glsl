#version 150

in vec3 vertexPosition;
in vec4 vertexColour;

uniform mat4 MVP;

out vec4 vertexColourOut;

void main()
{
	gl_Position = MVP *vec4(vertexPosition, 1.0);
	vertexColourOut = vertexColour;
}