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

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_executable (Spark "src/engine/Node.h" "src/Main.cpp" "src/engine/Node.cpp" "src/engine/Scene.h")

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

set_property(TARGET Spark PROPERTY CXX_STANDARD 26)