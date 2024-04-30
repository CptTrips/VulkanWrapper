#pragma once

#include <string>
#include <vector>

class ShaderReader
{

    std::vector<char> code;

public:
    ShaderReader(const std::string& filePath);

    const std::vector<char>& getCode() const;
};

