# Logging

Logging runs on its own thread in a producer-consumer pattern due to IO operations being slow.

## Getting Started
You can register your games logger using
`Spark::Logging::registerLogger(std::make_unique<Spark::Logging::Logger>(Spark::Logging::LogLevel::INFO, "loggerName");`

You can get a reference to a logger using
`Spark::Logging::getLogger("loggerName");`

SEVERE logs will flush output buffers (std::endl), but lower log levels will not.

# Logger Names
A name is a unique ID for your logger. It will be included in the log messages, and you will use it to get your logger, so it should probably be something short.
"spark" is used as Spark's engine logger.

# File Logging
Logs will be saved to `logs/<loggername>/` directory relative to your game executable.
The logger constructor takes in an optional boolean `fileLoggingEnabled` which you can use to toggle this functionality on a per logger basis.
By default file logging is enabled.

# Debug
Debug messages will only be sent if your logger level is set to INFO and you are running your game in debug mode.