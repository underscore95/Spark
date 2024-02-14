# Namespaces

Spark uses the Spark and SparkInternal namespaces.
Commonly used essential methods can be put directly into Spark / SparkInternal, though most things should have their own nested namespaces, e.g `SparkInternal::Logging` or `Spark::Logging`.
If you have one method that is used a lot, feel free to make an alias in the Spark or SparkInternal namespace, such as `Spark::getLogger()` being an alias for `Spark::Logging::getLogger()`.