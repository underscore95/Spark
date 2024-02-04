#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_Uv;

uniform vec2 u_Viewport;
uniform sampler2D u_Texture;

void main()
{
	colour = texture(u_Texture, v_Uv);
}