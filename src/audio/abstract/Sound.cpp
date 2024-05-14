#include "Sound.h"

#include "logging/Logger.h"

Spark::Audio::Sound::Sound(const std::string_view& path) : id(UINT_MAX)
{
	openFile(path);

	data.resize(count);
	readFile(data.data(), frames);

	closeFile();
}

Spark::Audio::Sound::~Sound()
{
	assert(id != UINT_MAX, "You forgot to call the createBuffer() function!");
	auto& logger = SparkInternal::getLogger();
	logger.debug("Deleted sound with ID: " + std::to_string(id));
}