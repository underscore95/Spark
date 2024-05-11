#include "Audio.h"

#include "logging/Logger.h"

#ifdef WIN32

#define SPARK_OPENAL

#endif



#ifdef SPARK_OPENAL

#include "audio/openal/OpenALAudio.h"

const SparkInternal::Audio::AudioFormat SparkInternal::Audio::MONO8 = AL_FORMAT_MONO8;
const SparkInternal::Audio::AudioFormat SparkInternal::Audio::MONO16 = AL_FORMAT_MONO16;
const SparkInternal::Audio::AudioFormat SparkInternal::Audio::STEREO8 = AL_FORMAT_STEREO8;
const SparkInternal::Audio::AudioFormat SparkInternal::Audio::STEREO16 = AL_FORMAT_STEREO16;

#endif

bool initialised = false;

namespace SparkInternal::Audio {
	void init() {
		if (initialised) [[unlikely]] {
			return;
			}

		initialised = true;
		auto& logger = SparkInternal::getLogger();


#ifdef SPARK_OPENAL
		SparkInternal::Audio::OpenAL::init();

		logger.info("Audio initialised using OpenAL");
#else
		logger.severe("No audio backend available. (Unsupported Platform)");
		return;
#endif
	}

	void exit() {
		if (!initialised) [[unlikely]] {
			return;
			}

		initialised = false;
		auto& logger = SparkInternal::getLogger();


#ifdef SPARK_OPENAL
		SparkInternal::Audio::OpenAL::exit();

		logger.info("Cleaned up audio.");
#endif
	}
}