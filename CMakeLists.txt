cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Version
project ("Spark" LANGUAGES CXX VERSION 0.16.0)
add_compile_definitions(-DSPARK_VERSION="v${CMAKE_PROJECT_VERSION}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # Need this for .lib

include(settings.cmake)
include(${VCPKG_PATH})

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_library(Spark SHARED
    "src/logging/Logger.cpp" "src/logging/Logger.h" "src/logging/Logging.cpp" "src/logging/Logging.h" "src/utils/DateUtils.h" "src/utils/DateUtils.cpp" "src/core/Application.cpp" "src/core/Application.h"  "src/Spark.h" "src/core/SparkEngine.h"   "src/logging/InternalLogging.h" "src/logging/InternalLogging.cpp" "src/events/Event.h" "src/events/EventHandler.h" "src/events/EventHandler.cpp" "src/events/EventListener.h" "src/events/EventListener.cpp"  "src/events/Events.h" "src/events/events/WindowResize.h" "src/events/EventContainer.h"  "src/pch.h"      "src/window/abstract/Window.h" "src/window/abstract/Window.cpp" "src/window/glfw/GLFWWindow.h" "src/window/glfw/GLFWWindow.cpp" "src/window/api/WindowFactory.h" "src/window/api/WindowFactory.cpp" "src/core/SparkEngine.cpp" "src/entities/BaseComponent.h" "src/entities/EntityManager.h" "src/entities/ComponentTypeRegistry.h" "src/entities/View.h" "src/entities/View.cpp" "src/systems/System.h" "src/systems/SystemManager.h" "src/systems/SystemManager.cpp" "src/graphics/abstract/buffers/Buffer.h" "src/graphics/abstract/buffers/IndexBuffer.h" "src/graphics/abstract/buffers/VertexBuffer.h" "src/graphics/abstract/buffers/VertexBufferLayout.h" "src/graphics/abstract/buffers/VertexArray.h" "src/graphics/opengl/buffers/VertexBuffer.h" "src/graphics/opengl/buffers/IndexBuffer.h" "src/graphics/opengl/buffers/IndexBuffer.cpp" "src/graphics/opengl/buffers/VertexBuffer.cpp" "src/graphics/opengl/buffers/VertexArray.h" "src/graphics/opengl/buffers/VertexArray.cpp" "src/graphics/api/camera/MVP.h" "src/graphics/api/camera/MVP.cpp" "src/graphics/abstract/shaders/Shader.h" "src/graphics/abstract/shaders/Shader.cpp"  "src/graphics/opengl/shaders/VertexShader.h" "src/graphics/opengl/shaders/VertexShader.cpp" "src/graphics/opengl/shaders/ShaderUtils.h" "src/graphics/opengl/shaders/FragmentShader.cpp" "src/graphics/opengl/shaders/FragmentShader.h" "src/graphics/abstract/shaders/ShaderProgram.h" "src/graphics/abstract/shaders/ShaderProgram.cpp" "src/graphics/opengl/shaders/ShaderProgram.h" "src/graphics/opengl/shaders/ShaderProgram.cpp" "src/graphics/abstract/Renderer.h" "src/graphics/opengl/Renderer.h" "src/graphics/opengl/Renderer.cpp" "src/graphics/api/GraphicsFactory.h" "src/graphics/api/GraphicsFactory.cpp" "src/graphics/opengl/buffers/VertexBufferLayout.h" "src/graphics/opengl/buffers/VertexBufferLayout.cpp"  "src/entities/EntityID.h" "src/entities/Entity.h" "src/vendor/stb/stb_image.cpp"   "src/graphics/abstract/textures/Texture.h" "src/macros.h" "src/graphics/opengl/textures/Texture.h" "src/graphics/opengl/textures/Texture.cpp" "src/graphics/abstract/textures/Texture.cpp" "src/graphics/api/camera/Camera.h" "src/graphics/api/camera/Camera.cpp" "src/graphics/opengl/shaders/ShaderUtils.cpp" "src/window/api/Input.h" "src/window/api/Input.cpp" "src/window/api/KeysAndButtons.h" "src/graphics/api/camera/CameraController.h"  "src/graphics/api/camera/KeyboardCameraController.h" "src/graphics/api/camera/KeyboardCameraController.cpp"  "src/graphics/api/camera/CameraController.cpp" "src/graphics/abstract/Material.h" "src/graphics/abstract/Material.cpp" "src/graphics/abstract/models/Model.h" "src/graphics/api/models/FileParserMTL.h" "src/graphics/api/models/FileParserMTL.cpp" "src/graphics/api/models/FileParserOBJ.h" "src/graphics/api/models/FileParserOBJ.cpp" "src/utils/WeakVector.h")

# Spark Dependencies
# Magic Enum (Utils)
find_package(magic_enum CONFIG REQUIRED)
target_link_libraries(Spark PRIVATE magic_enum::magic_enum)

# GLFW (Window)
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Spark PRIVATE glfw)

# GLM (Maths)
find_package(glm REQUIRED)
target_link_libraries(Spark PUBLIC glm::glm)

# OpenGL (Graphics)
find_package(OpenGL REQUIRED)
target_link_libraries(Spark PRIVATE OpenGL::GL)

find_package(GLEW REQUIRED)
target_link_libraries(Spark PRIVATE GLEW::GLEW)

# STB (Image Loader)
find_package(Stb REQUIRED)
target_include_directories(Spark PRIVATE ${Stb_INCLUDE_DIR})

# CPP Version
set_property(TARGET Spark PROPERTY CXX_STANDARD 26)

# Precompiled Headers
target_precompile_headers(Spark PRIVATE "src/pch.h")
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)

# Testing
enable_testing()

file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(SparkTests ${TEST_SOURCES})
set_property(TARGET SparkTests PROPERTY CXX_STANDARD 26)

include_directories(${CMAKE_SOURCE_DIR}/tests/)

# GTest
find_package(GTest CONFIG REQUIRED)
target_link_libraries(SparkTests PRIVATE GTest::gtest_main)
target_link_libraries(SparkTests PRIVATE Spark)

add_test(NAME SparkTests COMMAND SparkTests)

# Copy headers to output dir
# This copies .cpp too, idk how to fix that
add_custom_command(TARGET SparkTests
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include/
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}/include
)