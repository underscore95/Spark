#pragma once

#include "pch.h"
#include "Playable.h"

namespace Spark::Audio {
	class AudioFactory;

	class Sound : public Playable {
	protected:
		unsigned int id;
		std::vector<short> data;

		virtual void createBuffer() = 0;

		friend class Spark::Audio::AudioFactory;
	public:
		Sound(const std::string_view& path);
		virtual ~Sound();

		[[nodiscard]] const unsigned int getId() const { return id; }
	};
}