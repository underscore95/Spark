# Getting Started
You should call `Spark::init()` before doing anything with Spark!

## Supported Platforms
[x] Windows

## Spark.h
You can use `#include <Spark.h>` to include most important headers.

## First Steps
1. Create a new class that inherits from `Spark::Application`.
2. In your `int main()` method, call `Spark::init<YourApplication>();`.
3. Applications do not automatically have a window associated with them, you will need to create your own. See the windows documentation.
4. Applications will never stop unless you explicitly call the stop() method.