#pragma once
#include "GL/glew.h"
#include <vector>
#include "glm.hpp"
#include "vertex.h"
#include "logger.h"
#include <unordered_map>

using namespace std;
using namespace glm;

namespace corona
{
	class ArrayBuffer
	{
	public:
		using gl_enum = GLenum;
		
		ArrayBuffer();
		void genVao(); 
		void loadBuffer(const vector<vertex>& vertices, const vector<GLuint>& indices, const vector<mat4>& translations = vector<mat4>{});
		void setAttribute(int num, int comp, gl_enum type, size_t size, const void* offset);
		void setAttribDivisor(int attribute, int divisor);
		void reserve(int total, int perComponent);
		void bindVao();
		void unbindVao();
		void draw();
		void dynamicDraw(vector<vertex>& data);
		void drawInstances(int count);
		void clean();
	private:
		GLuint vaoID = 0, vboID = 0, eboID = 0, instanceVboID = 0;
		size_t indexCount;
	};


}
