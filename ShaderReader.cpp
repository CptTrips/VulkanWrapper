#include "ShaderReader.h"

#include <fstream>

ShaderReader::ShaderReader(const std::string& filePath)
{

	std::ifstream file(filePath, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

	size_t fileSize = (size_t) file.tellg();
	code = std::vector<char>(fileSize);

	file.seekg(0);
	file.read(code.data(), fileSize);

	file.close();
}

const std::vector<char>& ShaderReader::getCode() const
{

	return code;
}
