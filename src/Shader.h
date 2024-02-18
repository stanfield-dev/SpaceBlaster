#pragma once

#include <string>

class Shader
{
private:
	inline static unsigned int m_shaderID = 0;

public:
	static unsigned int compileShader(unsigned int, const std::string&);
	static int createShader(const std::string&, const std::string&);

	static void setShaderID(unsigned int);
	static unsigned int getShaderID();

	static void useShader(unsigned int);
	static void deleteShader(unsigned int);

	static std::string getFragmentShader();
	static std::string getVertexShader();
};

