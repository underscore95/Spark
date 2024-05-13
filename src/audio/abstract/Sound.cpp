#include "Sound.h"

#include <sndfile.hh>
#include "logging/Logger.h"

Spark::Audio::Sound::Sound(const std::string_view& path) : frequency(-1), format(-1), size(UINT_MAX), id(UINT_MAX)
{
	auto& logger = SparkInternal::getLogger();

	SF_INFO sfInfo;
	SNDFILE* file = sf_open(path.data(), SFM_READ, &sfInfo);

	if (!file) {
		logger.severe("Failed to open sound file: " + std::string(path));
		return;
	}

	frequency = sfInfo.samplerate;
	format = sfInfo.channels == 1 ? SparkInternal::Audio::MONO16 : SparkInternal::Audio::STEREO16;

	data.resize(sfInfo.frames * sfInfo.channels);
	sf_readf_short(file, data.data(), sfInfo.frames);

	sf_close(file);

	size = data.empty() ? 0 : data.size() * sizeof(data[0]);

	std::stringstream ss;
	ss << "Loaded sound file: " << path << " with " << frequency << "Hz, " << sfInfo.channels << " channels and " << size << " bytes and " << sfInfo.format << " format.";
	logger.info(ss);
}

Spark::Audio::Sound::~Sound()
{
	assert(id != UINT_MAX, "You forgot to call the createBuffer() function!");
	auto& logger = SparkInternal::getLogger();
	logger.debug("Deleted sound with ID: " + std::to_string(id));
}