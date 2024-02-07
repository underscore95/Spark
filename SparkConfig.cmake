include(CMakeFindDependencyMacro)

set(Spark_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/src)
set(Spark_LIBRARIES Spark)

include("${CMAKE_CURRENT_LIST_DIR}/SparkTargets.cmake")
