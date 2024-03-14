#include "Shader.h"
#include "logging/Logger.h"
#include "logging/Logging.h"

void Spark::Graphics::Shader::read(const std::string& sourceToInject)
{
	std::string line;
	std::ifstream stream(filePath);

	if (!stream.is_open()) {
		auto& logger = SparkInternal::getLogger();
		logger.severe("Failed to open file: " + filePath);
		return;
	}

	std::stringstream buffer;
	bool hasInjected = false;
	while (std::getline(stream, line)) {
		if (!hasInjected && (line.empty() || line[0] != '#')) {
			hasInjected = true;
			buffer << sourceToInject << '\n';
		}
		buffer << line << '\n';
	}

	source = buffer.str();
	stream.close();
}

Spark::Graphics::Shader::Shader(const std::string& filePath) : filePath{ filePath }, rendererId{ 0 }
{
#ifdef NDEBUG
	source = "";
	this->filePath = "";
#endif
}

const unsigned int Spark::Graphics::Shader::getRendererId() const
{
	return rendererId;
}
