#include "Listener.h"

#include "OpenAL.h"

namespace Spark::Audio::OpenAL {
	void Listener::setPosition(float x, float y, float z) {
		alListener3f(AL_POSITION, x, y, z);
		CHECK_AL_ERROR();
	}

	void Listener::setVelocity(float x, float y, float z) {
		alListener3f(AL_VELOCITY, x, y, z);
		CHECK_AL_ERROR();
	}

	void Listener::setOrientation(float forwardX, float forwardY, float forwardZ, float upX, float upY, float upZ) {
		const float orientation[] = { forwardX, forwardY, forwardZ, upX, upY, upZ };
		alListenerfv(AL_ORIENTATION, orientation);
		CHECK_AL_ERROR();
	}
}