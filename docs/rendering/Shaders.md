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

### List of all Spark Uniforms:
Name | Datatype | Shader types | Description
Sp_MVP | mat4 | Vertex | The model view projection matrix.