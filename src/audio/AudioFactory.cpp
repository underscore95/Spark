#include "AudioFactory.h"
#include "AudioPlatforms.h"

namespace Spark::Audio {
	Listener& AudioFactory::getListener() {
#ifdef SPARK_OPENAL
		static Spark::Audio::OpenAL::Listener listener;
#else
		std::unreachable();
#endif
		return listener;
	}

	std::shared_ptr<Sound> [[nodiscard]] AudioFactory::loadSound(const std::string_view& path) {
#ifdef SPARK_OPENAL
		auto sound = std::make_shared<Spark::Audio::OpenAL::Sound>(path);
#else
		std::unreachable();
#endif
		sound->createBuffer();
		return sound;
	}

	std::unique_ptr<Source> [[nodiscard]] AudioFactory::createSource(const Sound& sound) {
#ifdef SPARK_OPENAL
		return std::make_unique<Spark::Audio::OpenAL::Source>(sound);
#else
		std::unreachable();
#endif
	}
}