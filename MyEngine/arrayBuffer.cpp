#include "arrayBuffer.h"
namespace corona
{

	ArrayBuffer::ArrayBuffer() {}
	
	void ArrayBuffer::genVao()
	{
		glGenVertexArrays(1, &vaoID);
	}

	void ArrayBuffer::bindVao()
	{
		glBindVertexArray(vaoID);
	}


	void ArrayBuffer::unbindVao()
	{
		glBindVertexArray(NULL);
	}


	void ArrayBuffer::setAttribDivisor(int attribute, int divisor)
	{
		glVertexAttribDivisor(attribute, divisor);
	}

	void ArrayBuffer::setAttribute(int num, int comp, gl_enum type, size_t size, const void* offset)
	{
		glVertexAttribPointer(num, comp, type, GL_FALSE, size, offset);
		glEnableVertexAttribArray(num);
	}

	void ArrayBuffer::reserve(int total, int perComponent)
	{
		indexCount = total;
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, total * perComponent * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	}



	void ArrayBuffer::loadBuffer(const vector<vertex>& vertices, const vector<GLuint>& indices, const vector<mat4>& translations)
	{
			glGenBuffers(1, &vboID);
			glBindBuffer(GL_ARRAY_BUFFER, vboID);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
			indexCount = indices.size();

			glGenBuffers(1, &eboID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

			if (!translations.empty())
			{
				glGenBuffers(1, &instanceVboID);
				glBindBuffer(GL_ARRAY_BUFFER, instanceVboID);
				glBufferData(GL_ARRAY_BUFFER, translations.size() * sizeof(translations), &translations[0], GL_STATIC_DRAW);

			}
			logger::trace("No Buffer was loaded!");
	}

	

	void ArrayBuffer::draw()
	{
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	}

	void ArrayBuffer::dynamicDraw(vector <vertex> & data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(vertex), &data[0]);

		glDrawArrays(GL_TRIANGLES, 0, indexCount);
	}


	void ArrayBuffer::drawInstances(int count)
	{
		glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0, count);
	}

	void ArrayBuffer::clean()
	{
		glDeleteBuffers(1, &vboID);
		glDeleteBuffers(1, &eboID);
		if (instanceVboID > 0)
			glDeleteBuffers(1, &instanceVboID);

		glDeleteVertexArrays(1, &vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		glBindVertexArray(NULL);
	}

}