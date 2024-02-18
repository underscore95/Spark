cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Version
project ("Spark" LANGUAGES CXX VERSION 0.8.0)
add_compile_definitions(-DSPARK_VERSION="v${CMAKE_PROJECT_VERSION}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # Need this for .lib

include(C:/Users/unfea/Documents/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_library(Spark SHARED
    "src/logging/Logger.cpp" "src/logging/Logger.h" "src/logging/Logging.cpp" "src/logging/Logging.h" "src/utils/DateUtils.h" "src/utils/DateUtils.cpp" "src/core/Application.cpp" "src/core/Application.h"  "src/Spark.h" "src/core/SparkEngine.h"   "src/logging/InternalLogging.h" "src/logging/InternalLogging.cpp" "src/events/Event.h" "src/events/EventHandler.h" "src/events/EventHandler.cpp" "src/events/EventListener.h" "src/events/EventListener.cpp"  "src/events/Events.h" "src/events/events/WindowResize.h" "src/events/EventContainer.h"  "src/pch.h"      "src/window/abstract/Window.h" "src/window/abstract/Window.cpp" "src/window/glfw/GLFWWindow.h" "src/window/glfw/GLFWWindow.cpp" "src/window/api/WindowFactory.h" "src/window/api/WindowFactory.cpp" "src/core/SparkEngine.cpp" "src/entities/BaseComponent.h" "src/entities/EntityManager.h" "src/entities/ComponentTypeRegistry.h" "src/entities/View.h" "src/entities/View.cpp" "src/systems/System.h" "src/systems/SystemManager.h" "src/systems/SystemManager.cpp" "src/graphics/abstract/Buffer.h"  "src/graphics/abstract/VertexBufferLayout.h"   "src/graphics/abstract/VertexBuffer.h" "src/graphics/abstract/IndexBuffer.h" "src/graphics/opengl/IndexBuffer.h" "src/graphics/opengl/IndexBuffer.cpp" "src/graphics/opengl/VertexBuffer.cpp" "src/graphics/opengl/VertexBuffer.h" "src/graphics/opengl/VertexArray.h" "src/graphics/opengl/VertexArray.cpp")

# Spark Dependencies
find_package(magic_enum CONFIG REQUIRED)
target_link_libraries(Spark PRIVATE magic_enum::magic_enum)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Spark PRIVATE glfw)

find_package(glm REQUIRED)
target_link_libraries(Spark PUBLIC glm::glm)

find_package(GLEW REQUIRED)
target_link_libraries(Spark PRIVATE GLEW::GLEW)

# CPP Version
set_property(TARGET Spark PROPERTY CXX_STANDARD 26)

# Precompiled Headers
target_precompile_headers(Spark PRIVATE "src/pch.h")
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)

# Testing
enable_testing()

add_executable(SparkTests  "tests/EntitiesTest.cpp")
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
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}/include
)