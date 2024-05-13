#pragma once

#include "pch.h"
#include "audio/Audio.h"

namespace Spark::Audio {
	class AudioFactory;

	class Sound {
	protected:
		unsigned int id;
		size_t size;
		int frequency;
		SparkInternal::Audio::AudioFormat format;
		std::vector<short> data;

		virtual void createBuffer() = 0;

		friend class Spark::Audio::AudioFactory;
	public:
		Sound(const std::string_view& path);
		virtual ~Sound();

		[[nodiscard]] const unsigned int getId() const { return id; }
	};
}