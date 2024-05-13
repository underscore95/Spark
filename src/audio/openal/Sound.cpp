#include "Sound.h"

void Spark::Audio::OpenAL::Sound::createBuffer()
{
    alGenBuffers(1, &id);
	CHECK_AL_ERROR();
    alBufferData(id, format, data.data(), size, frequency);
	CHECK_AL_ERROR();
}

Spark::Audio::OpenAL::Sound::~Sound()
{
	alDeleteBuffers(1, &id);
	CHECK_AL_ERROR();
}