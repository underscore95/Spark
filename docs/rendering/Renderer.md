# Renderer

The renderer handles actually rendering onto a window. You should only have one renderer per window.

You can create a renderer with `Spark::Graphics::createRenderer(std::shared_ptr<Spark::Window::Window> window, std::shared_ptr<Spark::Graphics::Camera> camera);`.
Note that the renderer will share ownership of the window, the window should not be deleted until the renderer has been deleted.

You can draw to the screen with `draw(const VertexArray& vertexArray);`.
Note that you must use `startDrawing(std::shared_ptr<Material> material)` and `stopDrawing()` before and after your draw calls.