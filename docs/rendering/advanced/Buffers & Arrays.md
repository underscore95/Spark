# Buffers & Arrays

## Vertex
A vertex is a collection of data, such as positions, texture coordinates, normals, etc.

## Vertex Buffer
A vertex buffer is an array of vertices that is sent to the GPU.

You can create a vertex buffer with `Spark::Graphics::createVertexBufferLayout();`.

### Vertex Buffer Layout
You can specify your vertex buffer data in any layout you like, however you must create a VertexBufferLayout to tell the GPU how your data is structured.

```
std::unique_ptr<Spark::Graphics::VertexBufferLayout> layout = Spark::Graphics::createVertexBufferLayout();
layout->pushFloat(2); // 2D Position Coordinates
layout->pushFloat(2); // Texture Coordinates
```

## Index Buffer
An index buffer is an array of indexes of the vertex buffer that is sent to the GPU.
For example, `const unsigned int* indices = new unsigned int[] { 0, 1, 2};` will draw the first, second, and third vertices in the vertex buffer (in that order).
Make sure you pass valid indices.

You can create a index buffer with `Spark::Graphics::createIndexBufferLayout();`.

## Vertex Array
A vertex array is simply a container for a vertex buffer, index buffer, and vertex buffer layout.
Ownership is transferred to the vertex array.

Example:
```
// Assumes indexBuffer, vertexBuffer, and layout are unique pointers.
Spark::Graphics::createVertexArray(std::move(indexBuffer), std::move(vertexBuffer), std::move(layout));
```