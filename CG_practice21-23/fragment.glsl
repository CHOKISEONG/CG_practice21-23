#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 Fragcolor;

void main ()
{
	float ambientLight = 0.5;
	vec3 ambient = ambientLight * lightColor;

	vec3 result = ambient * objectColor;

	Fragcolor = vec4(result, 1.0);
}