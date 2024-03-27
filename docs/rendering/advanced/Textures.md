# Textures

## Loading
You can load a texture with `Spark::Graphics::loadTexture("file path");`.
The file path should be relative to your games executable.

## Texture Slots
Most GPUs have 8-32 texture slots.
The TextureSlot type represents a texture slot (it is a signed short).

You can bind a texture to a texture slot using `texture.bind(slot);`.
The default value for `slot` is 0.

Negative slot numbers are considered invalid.

Spark supports texture slots 0 to 31.
OpenGL supports texture slots 0 to 31.

## Sampler2D
Sampler2D is a type in GLSL (read https://www.khronos.org/opengl/wiki/Sampler_(GLSL) for more information) that represents a texture.
Many sampler2D uniforms are injected into your fragment shader by Spark, see shaders documentation for a list.

Example fragment shader:
```
#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_Uv;

uniform sampler2D u_Texture;

void main()
{
	colour = texture(u_Texture, v_Uv);
}
```

Read the shader documentation for more information.