#include "Source.h"

namespace Spark::Audio::OpenAL {

	Source::Source(const Spark::Audio::Sound& sound) : Spark::Audio::Source(sound) {
		alGenSources(1, &id);
		CHECK_AL_ERROR();

		setPitch(1.0f);
		setGain(1.0f);
		setPosition(0.0f, 0.0f, 0.0f);
		setVelocity(0.0f, 0.0f, 0.0f);
	}

	Source::~Source()
	{
		alDeleteSources(1, &id);
		CHECK_AL_ERROR();
	}

	void Source::setPitch(float pitch) {
		alSourcef(id, AL_PITCH, pitch);
		CHECK_AL_ERROR();
	}

	void Source::setGain(float gain) {
		alSourcef(id, AL_GAIN, gain);
		CHECK_AL_ERROR();
	}

	void Source::setPosition(float x, float y, float z) {
		alSource3f(id, AL_POSITION, x, y, z);
		CHECK_AL_ERROR();
	}

	void Source::setVelocity(float x, float y, float z) {
		alSource3f(id, AL_VELOCITY, x, y, z);
		CHECK_AL_ERROR();
	}

	void Source::play() {
		alSourcei(id, AL_BUFFER, soundBufferId);
		CHECK_AL_ERROR();
		alSourcePlay(id);
		CHECK_AL_ERROR();
	}
}