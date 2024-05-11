#pragma once

#include "audio/abstract/Source.h"
#include "OpenAL.h"

namespace Spark::Audio::OpenAL {
	class Source : public Spark::Audio::Source {
	private:

	public:
		Source(const Spark::Audio::Sound& sound);
		~Source();

		void setPitch(float pitch) override;
		void setGain(float gain) override;
		void setPosition(float x, float y, float z) override;
		void setVelocity(float x, float y, float z) override;

		void play() override;
	};
}