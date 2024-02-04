# CMakeList.txt : CMake project for OpenGLProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Spark")

include(C:/Users/unfea/Documents/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Add source to this project's executable.
add_executable (Spark "src/Main.cpp" "src/graphics/shaders/Shader.h" "src/graphics/shaders/Shader.cpp" "src/graphics/shaders/ShaderProgram.h" "src/graphics/shaders/ShaderProgram.cpp" "src/errors/OpenGLErrorHandler.h" "src/errors/OpenGLErrorHandler.cpp" "src/graphics/buffers/Buffer.h"  "src/graphics/Renderer.h" "src/graphics/Renderer.cpp" "src/graphics/buffers/Buffer.cpp" "src/graphics/VertexArray.h" "src/graphics/VertexArray.cpp"  "src/graphics/buffers/BufferLayout.h"   "src/graphics/buffers/IndexBuffer.h" "src/graphics/buffers/VertexBuffer.h" "src/graphics/TypeConverter.h" "src/stb/stb_image.cpp" "src/stb/stb_image.h" "src/graphics/textures/Texture.h" "src/graphics/textures/Texture.cpp" "src/stb/stb_image.h" "src/graphics/MVP.h" "src/graphics/MVP.cpp")

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)    
find_package(spdlog REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

target_link_libraries(Spark glfw OpenGL::GL glm::glm GLEW::GLEW spdlog::spdlog magic_enum::magic_enum)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/resources
        COMMENT "https://www.youtube.com/watch?v=sTuIRzrB2dA")

add_dependencies(Spark copy_resources)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Spark PROPERTY CXX_STANDARD 20)
endif()
