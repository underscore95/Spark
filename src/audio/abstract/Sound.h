#pragma once

#include "pch.h"
#include "audio/Audio.h"

namespace Spark::Audio {
	class Sound {
	public:
		unsigned int id;
		size_t size;
		int frequency;
		SparkInternal::Audio::AudioFormat format;
		std::vector<float> data;

		virtual void createBuffer() = 0;
	public:
		Sound(const std::string_view& path);
		~Sound();

		[[nodiscard]] const unsigned int getId() const { return id; }
	};
}