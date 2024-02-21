#include "Shader.h"
#include "logging/Logger.h"
#include "logging/Logging.h"

void Spark::Graphics::Shader::read()
{
	std::string line;
	std::ifstream stream(filePath);

	if (!stream.is_open()) {
		auto& logger = SparkInternal::getLogger();
		logger.severe("Failed to open file: " + filePath);
		return;
	}

	std::stringstream buffer;
	while (std::getline(stream, line)) {
		buffer << line << '\n';
	}
	source = buffer.str();
	stream.close();
}

Spark::Graphics::Shader::Shader(const std::string& filePath) : filePath{ filePath }
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
