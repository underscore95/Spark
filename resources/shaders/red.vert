#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 v_Uv;

uniform mat4 u_MVP; // model view projection matrix

void main()
{
	gl_Position = u_MVP * position;
	v_Uv = uv;
};