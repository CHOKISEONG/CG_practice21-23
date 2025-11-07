#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;

uniform mat4 view;
uniform mat4 projection;

out vec3 out_color;

void main() 
{
	gl_Position =  projection * view * vec4(in_position.x, in_position.y, in_position.z, 1.0); 

	out_color = in_color;
}