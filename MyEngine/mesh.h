#pragma once
#include "GL/glew.h"
#include <vector>
#include "glm.hpp"
#include "scene.h"
#include "material.h"
#include "arrayBuffer.h"

using namespace glm;

namespace corona
{
	class mesh
	{
	private:
		ArrayBuffer* m_vertexBuffer;
		std::vector<vertex> m_vertices;
		std::vector<GLuint> m_indices;
		std::vector<material*> m_materials;
		std::vector<texture*> m_textures;
		std::vector<vec3> m_tangents;
	public:
		mesh();
		void writeMeshData(aiMesh* mesh, std::ofstream& file, std::vector<std::string>& materialNames);
		void loadMeshFromMemory(std::ifstream& file);
		void loadIntoBuffers(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<mat4>& translations = std::vector<mat4>{});
		void loadMaterial(const char* materialPath, int materialIndex);
		void draw(shaderManager& program);
		void drawInstances(shaderManager& program, int count);
		void clean();
		std::vector<vertex>& getVertices();
		std::vector<GLuint>& getIndices();
		std::vector<material*>& getMaterials();
		ArrayBuffer* getVertexBuffer() const;
};
}