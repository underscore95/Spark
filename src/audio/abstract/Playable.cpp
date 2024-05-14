#include "Playable.h"
#include "Playable.h"
#include "Playable.h"

#include <sndfile.hh>
#include "logging/Logger.h"

void Spark::Audio::Playable::openFile(const std::string_view& path) {
	auto& logger = SparkInternal::getLogger();
	if (isFileOpen) [[unlikely]] {
		logger.debug("Attempted to open already-open sound file");
		return;
	}

	SF_INFO sfInfo;
	file = sf_open(path.data(), SFM_READ, &sfInfo);
	if (!file) {
		logger.severe("Failed to open sound file: " + std::string(path));
		return;
	}

	isFileOpen = true;

	frames = sfInfo.frames;
	frequency = sfInfo.samplerate;
	format = sfInfo.channels == 1 ? SparkInternal::Audio::MONO16 : SparkInternal::Audio::STEREO16;
	count = sfInfo.frames * sfInfo.channels;
	size = count * sizeof(short);
}

void Spark::Audio::Playable::readFile(short* buffer, size_t amount)
{
	if (!isFileOpen) [[unlikely]] {
		auto& logger = SparkInternal::getLogger();
		logger.debug("Attempted to read from not-open sound file");
		return;
	}

	sf_read_short((SNDFILE*)file, buffer, amount);
}

void Spark::Audio::Playable::closeFile()
{
	if (!isFileOpen) [[unlikely]] {
		auto& logger = SparkInternal::getLogger();
		logger.debug("Attempted to close not-open sound file");
		return;
	}

	sf_close((SNDFILE*)file);
	isFileOpen = false;
}

Spark::Audio::Playable::~Playable()
{
#ifdef NDEBUG
	closeFile();
#else
	if (isFileOpen) {
		closeFile();
	}
#endif
}
