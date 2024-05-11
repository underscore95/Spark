#pragma once

#include "audio/abstract/Sound.h"
#include "OpenAL.h"

namespace Spark::Audio::OpenAL {
	class Sound : public Spark::Audio::Sound {
	public:
		void createBuffer() override;
	public:
		Sound(const std::string_view& path) : Spark::Audio::Sound(path) {};
		~Sound();
	};
}