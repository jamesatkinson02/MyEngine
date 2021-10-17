#pragma once
#include "GL/glew.h"
#include <string>

namespace corona
{
	class logger
	{
	public:
		static void error_(int line, const char* file, std::string desc);
		#define error(desc) error_(__LINE__, __FILE__, desc);
		static GLenum glCheckError_(int line, const char* file);
		#define glCheckError() glCheckError_(__LINE__, __FILE__);
		static void trace(std::string desc);
	};
}
