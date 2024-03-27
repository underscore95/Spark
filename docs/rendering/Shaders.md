# Shaders

A shader is a program that runs on the GPU.

Spark currently supports Vertex Shaders (runs for every vertex) and Fragment Shaders (runs for every fragment (similar to a pixel)).

You can create a shader using:
```
Spark::Graphics::createVertexShader(const std::string& filePath);
Spark::Graphics::createFragmentShader(const std::string& filePath);
```

Shaders can be combined into a single ShaderProgram:
```
std::vector<Spark::Graphics::Shader> shaders = { vertexShader, fragmentShader };
std::unique_ptr<Spark::Graphics::ShaderProgram> program = Spark::Graphics::createShaderProgram(shaders);
```

Once a program has been created, the shaders are free to be deleted.

See Renderer documentation for how to apply a shader.

## Uniforms
Data can be sent to the shader using uniform variables, example:
```
// CPU
program->setUniform2f("u_SomeVector", x, y);

// GPU (Shader)
uniform vec2 u_SomeVector; // Usually uniforms are prefixed with u, however this is not enforced by the compiler.
```

## Spark Uniforms

Some uniforms are automatically injected into your shader by Spark. These uniforms are always prefixed with `Sp_`.
For example, `Sp_MVP` is injected into your vertex shader, so the following is a valid Spark vertex shader:
```
#version 330 core

layout(location = 0) in vec4 position;

void main() {
	gl_Position = Sp_MVP * position; // Multiply position by model view projection matrix to get the position after all transformations (including camera).
}
```

Note that if a sampler2D is equal to -1, it is an invalid texture.

### List of all Spark Uniforms:
Name | Datatype | Shader types | Description
Sp_MVP | mat4 | Vertex | The model view projection matrix.
Sp_ActiveTexture | sampler2D | Fragment | Active texture in the current material
Sp_Texture_0  |  sampler2D  |  Fragment  |  Texture bound to slot 0
Sp_Texture_1  |  sampler2D  |  Fragment  |  Texture bound to slot 1
Sp_Texture_2  |  sampler2D  |  Fragment  |  Texture bound to slot 2
Sp_Texture_3  |  sampler2D  |  Fragment  |  Texture bound to slot 3
Sp_Texture_4  |  sampler2D  |  Fragment  |  Texture bound to slot 4
Sp_Texture_5  |  sampler2D  |  Fragment  |  Texture bound to slot 5
Sp_Texture_6  |  sampler2D  |  Fragment  |  Texture bound to slot 6
Sp_Texture_7  |  sampler2D  |  Fragment  |  Texture bound to slot 7
Sp_Texture_8  |  sampler2D  |  Fragment  |  Texture bound to slot 8
Sp_Texture_9  |  sampler2D  |  Fragment  |  Texture bound to slot 9
Sp_Texture_10  |  sampler2D  |  Fragment  |  Texture bound to slot 10
Sp_Texture_11  |  sampler2D  |  Fragment  |  Texture bound to slot 11
Sp_Texture_12  |  sampler2D  |  Fragment  |  Texture bound to slot 12
Sp_Texture_13  |  sampler2D  |  Fragment  |  Texture bound to slot 13
Sp_Texture_14  |  sampler2D  |  Fragment  |  Texture bound to slot 14
Sp_Texture_15  |  sampler2D  |  Fragment  |  Texture bound to slot 15
Sp_Texture_16  |  sampler2D  |  Fragment  |  Texture bound to slot 16
Sp_Texture_17  |  sampler2D  |  Fragment  |  Texture bound to slot 17
Sp_Texture_18  |  sampler2D  |  Fragment  |  Texture bound to slot 18
Sp_Texture_19  |  sampler2D  |  Fragment  |  Texture bound to slot 19
Sp_Texture_20  |  sampler2D  |  Fragment  |  Texture bound to slot 20
Sp_Texture_21  |  sampler2D  |  Fragment  |  Texture bound to slot 21
Sp_Texture_22  |  sampler2D  |  Fragment  |  Texture bound to slot 22
Sp_Texture_23  |  sampler2D  |  Fragment  |  Texture bound to slot 23
Sp_Texture_24  |  sampler2D  |  Fragment  |  Texture bound to slot 24
Sp_Texture_25  |  sampler2D  |  Fragment  |  Texture bound to slot 25
Sp_Texture_26  |  sampler2D  |  Fragment  |  Texture bound to slot 26
Sp_Texture_27  |  sampler2D  |  Fragment  |  Texture bound to slot 27
Sp_Texture_28  |  sampler2D  |  Fragment  |  Texture bound to slot 28
Sp_Texture_29  |  sampler2D  |  Fragment  |  Texture bound to slot 29
Sp_Texture_30  |  sampler2D  |  Fragment  |  Texture bound to slot 30
Sp_Texture_31  |  sampler2D  |  Fragment  |  Texture bound to slot 31
