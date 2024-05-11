#pragma once

#include "logging/Logger.h"
#include <AL/al.h>
#include <AL/alc.h>
#include "pch.h"

#define CHECK_AL_ERROR() \
do { \
    ALenum error = alGetError(); \
    if (error != AL_NO_ERROR) { \
        std::stringstream _OPENAL_ERROR_SS; \
        _OPENAL_ERROR_SS << "OpenAL error: "; \
        switch(error) \
        { \
        case AL_INVALID_NAME: \
            _OPENAL_ERROR_SS << "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function"; \
            break; \
        case AL_INVALID_ENUM: \
            _OPENAL_ERROR_SS << "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function"; \
            break; \
        case AL_INVALID_VALUE: \
            _OPENAL_ERROR_SS << "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function"; \
            break; \
        case AL_INVALID_OPERATION: \
            _OPENAL_ERROR_SS << "AL_INVALID_OPERATION: the requested operation is not valid"; \
            break; \
        case AL_OUT_OF_MEMORY: \
            _OPENAL_ERROR_SS << "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory"; \
            break; \
        default: \
            _OPENAL_ERROR_SS << "UNKNOWN AL ERROR"; \
        } \
        _OPENAL_ERROR_SS << " (code " << error << ") at " << __FILE__ << ":" << __LINE__; \
        auto& _SPARK_LOGGER = SparkInternal::getLogger(); \
        _SPARK_LOGGER.severe(_OPENAL_ERROR_SS.str()); \
    } \
} while (0)