#pragma once

#include "audio/abstract/Sound.h"
#include "OpenAL.h"

namespace Spark::Audio::OpenAL {
	class Sound : public Spark::Audio::Sound {
	protected:
		friend class Spark::Audio::AudioFactory;
		void createBuffer() override;
	public:
		Sound(const std::string_view& path) : Spark::Audio::Sound(path) {};
		~Sound();
	};
}