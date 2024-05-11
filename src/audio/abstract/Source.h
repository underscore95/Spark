#pragma once

#include "Sound.h"

namespace Spark::Audio {
	class Source {
	protected:
		unsigned int soundBufferId;
		unsigned int id;
	public:
		Source(const Sound& sound) : soundBufferId{ sound.getId() }, id{ UINT_MAX } {};

		virtual	void setPitch(float pitch) = 0;
		virtual	void setGain(float gain) = 0;
		virtual void setPosition(float x, float y, float z) = 0;
		virtual void setVelocity(float x, float y, float z) = 0;

		virtual void play() = 0;

		[[nodiscard]] const int getId() const { return id; }
	};
}