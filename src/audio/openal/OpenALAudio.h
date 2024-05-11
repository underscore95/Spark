#pragma once

#include "OpenAL.h"

namespace SparkInternal::Audio::OpenAL {

	extern ALCdevice* device;
	extern ALCcontext* context;

	void init();
	void exit();
}