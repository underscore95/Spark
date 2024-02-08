# Getting Started

## Supported Platforms
[x] Windows

## Spark.h
You can use `#include <Spark.h>` to include most important headers.

## Applications
Create a new class that inherits from `Spark::Application` and overrides the `start()` method.
In your `int main()` method, create an instance of your application on the heap and call the start method.
Don't forget to delete your application before your program ends (good practice!)