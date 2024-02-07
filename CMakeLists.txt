# CMakeList.txt : CMake project for Spark, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Spark" LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(C:/Users/unfea/Documents/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_library(Spark SHARED
    "src/logging/Logger.cpp" "src/logging/Logger.h" "src/logging/Logging.cpp" "src/logging/Logging.h" "src/utils/DateUtils.h" "src/utils/DateUtils.cpp")

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

target_link_libraries(Spark PRIVATE glfw OpenGL::GL glm::glm GLEW::GLEW magic_enum::magic_enum)

set_property(TARGET Spark PROPERTY CXX_STANDARD 26)
