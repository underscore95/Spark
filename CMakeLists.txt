# CMakeList.txt : CMake project for OpenGLProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OpenGLProject")

include(C:/Users/unfea/Documents/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Add source to this project's executable.
add_executable (OpenGLProject "src/Main.cpp" "src/opengl/shaders/Shader.h" "src/opengl/shaders/Shader.cpp" "src/opengl/shaders/ShaderProgram.h" "src/opengl/shaders/ShaderProgram.cpp" "src/errors/OpenGLErrorHandler.h" "src/errors/OpenGLErrorHandler.cpp" "src/opengl/buffers/Buffer.h"  "src/opengl/Renderer.h" "src/opengl/Renderer.cpp" "src/opengl/buffers/Buffer.cpp" "src/opengl/VertexArray.h" "src/opengl/VertexArray.cpp"  "src/opengl/buffers/BufferLayout.h"   "src/opengl/buffers/IndexBuffer.h" "src/opengl/buffers/VertexBuffer.h" "src/opengl/TypeConverter.h" "src/stb/stb_image.cpp" "src/stb/stb_image.h" "src/opengl/textures/Texture.h" "src/opengl/textures/Texture.cpp" "src/stb/stb_image.h" "src/opengl/MVP.h" "src/opengl/MVP.cpp")

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)    
find_package(spdlog REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

target_link_libraries(OpenGLProject glfw OpenGL::GL glm::glm GLEW::GLEW spdlog::spdlog magic_enum::magic_enum)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/resources
        COMMENT "https://www.youtube.com/watch?v=sTuIRzrB2dA")

add_dependencies(OpenGLProject copy_resources)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGLProject PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
