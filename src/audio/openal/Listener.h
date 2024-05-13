#pragma once

#include "audio/abstract/Listener.h"

namespace Spark::Audio::OpenAL {
	class Listener : public Spark::Audio::Listener {
	public:

		void setPosition(float x, float y, float z) override;
		void setVelocity(float x, float y, float z) override;
		void setOrientation(float forwardX, float forwardY, float forwardZ, float upX, float upY, float upZ) override;
	};
}