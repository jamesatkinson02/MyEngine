#include "logger.h"
#include <iostream>

using namespace corona;

void logger::trace(std::string desc)
{
	std::cout << "[LOG]: " << desc << '\n';
}

void logger::error_(int line, const char* file, std::string desc)
{
	std::cerr << "[ERROR]: " << desc << " in " << file << " at line " << line << '\n';
}

GLenum logger::glCheckError_(int line, const char* file)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string errorMsg;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  errorMsg = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 errorMsg = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             errorMsg = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                errorMsg = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               errorMsg = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 errorMsg = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: errorMsg = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		logger::error_(line, file, errorMsg);
	}
	return errorCode;
}
