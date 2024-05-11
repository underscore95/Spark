#include "OpenALAudio.h"
#include "logging/Logger.h"

#include "pch.h"

namespace SparkInternal::Audio::OpenAL {
	ALCdevice* device = nullptr;
	ALCcontext* context = nullptr;

	void init() {
		auto& logger = SparkInternal::getLogger();

		
		device = alcOpenDevice(nullptr);
		if (!device) [[unlikely]] {
			logger.severe("Failed to initialise OpenAL device.");
			return;
			}

		context = alcCreateContext(device, nullptr);
		if (!context) [[unlikely]] {
			logger.severe("Failed to create OpenAL context.");
			exit();
			return;
			}

		alcMakeContextCurrent(context);
		CHECK_AL_ERROR();
	}

	void exit() {
		alcMakeContextCurrent(nullptr);
		CHECK_AL_ERROR();

		if (context) {
			alcDestroyContext(context);
			CHECK_AL_ERROR();
		}

		if (device) {
			alcCloseDevice(device);
			CHECK_AL_ERROR();
		}
	}
}