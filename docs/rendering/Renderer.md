# Renderer

The renderer handles actually rendering onto a window. You should only have one renderer per window.

You can create a renderer with `Spark::Graphics::createRenderer(std::shared_ptr<Spark::Window::Window> window);`.
Note that the renderer will share ownership of the window, the window should not be deleted until the renderer has been deleted.

You should be clearing the frame at the start of your rendering with `clear();`.
You can draw to the screen with `draw(const VertexArray& vertexArray, const ShaderProgram& shaders);`.