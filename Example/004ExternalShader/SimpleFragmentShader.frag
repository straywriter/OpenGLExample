#version 330 core

// Ouput data
out vec3 color;
uniform vec3 TriangleColor;

void main()
{
	// Output color = red 
	color = TriangleColor;
}