#pragma once

#include "audio/Audio.h"

namespace Spark::Audio {
	class Playable {
	private:
		void* file{ nullptr };
		bool isFileOpen = false;
	protected:
		size_t size{ UINT_MAX };
		size_t count{ UINT_MAX };
		size_t frames{ UINT_MAX };
		int frequency{ -1 };
		SparkInternal::Audio::AudioFormat format{ SparkInternal::Audio::INVALID_AUDIO_FORMAT };

		void openFile(const std::string_view& path);
		void readFile(short* buffer, size_t amount);
		void closeFile();

	public:
		~Playable();
	};
}