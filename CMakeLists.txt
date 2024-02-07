cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Spark" LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(C:/Users/unfea/Documents/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_library(Spark SHARED
    "src/logging/Logger.cpp" "src/logging/Logger.h" "src/logging/Logging.cpp" "src/logging/Logging.h" "src/utils/DateUtils.h" "src/utils/DateUtils.cpp" "src/core/Application.cpp" "src/core/Application.h"  "src/Spark.h")

find_package(magic_enum CONFIG REQUIRED)

target_link_libraries(Spark PRIVATE magic_enum::magic_enum)

set_property(TARGET Spark PROPERTY CXX_STANDARD 26)

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

