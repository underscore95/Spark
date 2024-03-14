# Getting Spark Running

1. Clone the main branch of Spark
2. settings.cmake
2.1. Install vcpkg
2.2. Using settings.cmake.example as a base, create a settings.cmake file.
3. Use vcpkg to install all dependencies (look for `find_package` in `CMakeLists.txt`).
4. Build Spark by running SparkTests.exe target in both debug and release mode.
5. Include Spark into your game's `CMakeLists.txt` using https://github.com/underscore95/SparkGame as an example.
5.1. Copy Spark.dll and Spark.lib into the same folder as your game's executable.
5.2. Ensure you include debug libraries for debug mode and release libraries for release mode.
6. Launch your game!