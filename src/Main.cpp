#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/shaders/ShaderProgram.h"
#include <spdlog/spdlog.h>
#include "errors/OpenGLErrorHandler.h"
#include <magic_enum.hpp>
#include "graphics/buffers/Buffer.h"
#include <cassert>
#include "graphics/buffers/BufferLayout.h"
#include "graphics/buffers/VertexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Renderer.h"
#include "graphics/textures/Texture.h"
#include <glm/glm.hpp>
#include "graphics/MVP.h"

int main(int argc, char** argv) {
	assert(sizeof(unsigned int) == sizeof(GLuint));

	int windowWidth = 1280;
	int windowHeight = 720;
	GLFWwindow* window;

	glm::vec3 cameraPos(0, 0, 0);

	GL::MVP mvp;
	mvp.setProj(glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f));
	mvp.setView(glm::translate(glm::identity<glm::mat4>(), -cameraPos)); // Invert camera pos
	mvp.setModel(glm::translate(glm::identity<glm::mat4>(), glm::vec3(250, 250, 0)));

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// Create window and OpenGL context
	window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		// Problem: glewInit failed, something is seriously wrong.
		spdlog::error("glewInit error: {}", (char*)glewGetErrorString(err));
		return -1;
	}

	// Print out versions
	spdlog::info("Resolution: {}x{}", windowWidth, windowHeight);
	spdlog::info("Log Level: {}", magic_enum::enum_name(spdlog::get_level()));
	spdlog::info("OpenGL Version {}", (char*)glGetString(GL_VERSION));
	spdlog::info("GLEW Version {}", (char*)glewGetString(GLEW_VERSION));
	spdlog::info("GLFW Version {}", (char*)glfwGetVersionString());

	OpenGLErrorHandler openGLErrorHandler;
	openGLErrorHandler.addDebugCallback();

	glfwSwapInterval(1);
	{
		GL::Renderer renderer;

		// VAO
		GL::VertexArray vertexArray;
		vertexArray.bind();

		// Vertices
		const size_t VERTEX_COUNT = 4;
		const float* vertices = new float[] {
			-100.0f, -100.0f, 0.0f, 0.0f,
				100.0f, -100.0f, 1.0f, 0.0f,
				100.0f, 100.0f, 1.0f, 1.0f,
				-100.0f, 100.0f, 0.0f, 1.0f
			};

		GL::BufferLayout verticesLayout;
		verticesLayout.push<float>(2); // positions
		verticesLayout.push<float>(2); // texture coordinates
		GL::VertexBuffer verticesBuffer(GL_STATIC_DRAW, VERTEX_COUNT * verticesLayout.getStride(), vertices);
		vertexArray.addVertexBuffer(verticesBuffer, verticesLayout);

		// Indices
		const size_t INDICES_COUNT = 6;
		const size_t INDEX_SIZE = sizeof(unsigned int);
		const unsigned int* indices = new unsigned int[] {
			0, 1, 2,
				2, 3, 0
			};

		GL::IndexBuffer indicesBuffer(GL_STATIC_DRAW, INDICES_COUNT, INDEX_SIZE, indices);
		vertexArray.addIndexBuffer(indicesBuffer);

		// Shaders
		Shader vertexShader("resources/shaders/red.vert", GL_VERTEX_SHADER);
		Shader fragmentShader("resources/shaders/red.frag", GL_FRAGMENT_SHADER);

		std::vector<Shader> shaders = { vertexShader, fragmentShader };
		ShaderProgram program(shaders);

		// Textures
		GL::Texture texture("resources/textures/image.png");
		int textureSlot = 0;
		texture.bind(textureSlot);

		while (!glfwWindowShouldClose(window))
		{
			// Input
			glfwPollEvents();

			// Update
			const int oldWidth = windowWidth, oldHeight = windowHeight;
			glfwGetWindowSize(window, &windowWidth, &windowHeight);
			if (oldWidth != windowWidth || oldHeight != windowHeight) {
				// Window size changed
				spdlog::info("Resolution: {}x{}", windowWidth, windowHeight);
				mvp.setProj(glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f));
			}

			program.bind();
			program.setUniform1i("u_Texture", textureSlot);
			//program.setUniform2f("u_Viewport", windowWidth, windowHeight);
			program.setUniformMat4f("u_MVP", mvp.getMVP());

			// Render
			renderer.clearFrame();

			renderer.draw(vertexArray, program);

			glfwSwapBuffers(window);
		}
	}

	glfwTerminate();
	return 0;
}