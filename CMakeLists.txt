cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Version
project ("Spark" LANGUAGES CXX VERSION 0.5.0)
add_compile_definitions(-DSPARK_VERSION="v${CMAKE_PROJECT_VERSION}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # Need this for .lib

include(C:/Users/unfea/Documents/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_library(Spark SHARED
    "src/logging/Logger.cpp" "src/logging/Logger.h" "src/logging/Logging.cpp" "src/logging/Logging.h" "src/utils/DateUtils.h" "src/utils/DateUtils.cpp" "src/core/Application.cpp" "src/core/Application.h"  "src/Spark.h" "src/core/SparkEngine.h"   "src/logging/InternalLogging.h" "src/logging/InternalLogging.cpp" "src/events/Event.h" "src/events/EventHandler.h" "src/events/EventHandler.cpp" "src/events/EventListener.h" "src/events/EventListener.cpp"  "src/events/Events.h" "src/events/events/WindowResize.h" "src/events/EventContainer.h"  "src/pch.h"      "src/window/abstract/Window.h" "src/window/abstract/Window.cpp" "src/window/glfw/GLFWWindow.h" "src/window/glfw/GLFWWindow.cpp" "src/window/api/WindowFactory.h" "src/window/api/WindowFactory.cpp" "src/core/SparkEngine.cpp" "src/entities/BaseComponent.h" "src/entities/EntityManager.h")

find_package(magic_enum CONFIG REQUIRED)
target_link_libraries(Spark PRIVATE magic_enum::magic_enum)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Spark PRIVATE glfw)

find_package(glm REQUIRED)
target_link_libraries(Spark PUBLIC glm::glm)

set_property(TARGET Spark PROPERTY CXX_STANDARD 26)

# Precompiled Headers
target_precompile_headers(Spark PRIVATE "src/pch.h")
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)

# Set the installation directory for your library
set(INSTALL_DESTINATION lib)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")

# Define the target to install (your game engine library)
install(TARGETS Spark
        EXPORT SparkTargets
        LIBRARY DESTINATION ${INSTALL_DESTINATION}
        ARCHIVE DESTINATION ${INSTALL_DESTINATION}
        RUNTIME DESTINATION ${INSTALL_DESTINATION}
        INCLUDES DESTINATION include)

# Export the target
install(EXPORT SparkTargets
       FILE "SparkTargets.cmake"
       NAMESPACE Spark::
       DESTINATION ${INSTALL_DESTINATION})

# Install the package configuration file
install(FILES ${CMAKE_SOURCE_DIR}/SparkConfig.cmake
        DESTINATION ${INSTALL_DESTINATION})

