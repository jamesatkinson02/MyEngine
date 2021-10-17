#include "mesh.h"
#include "logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

using namespace corona; 

mesh::mesh()
{
}

void mesh::writeMeshData(aiMesh* mesh, std::ofstream& file, std::vector<std::string>& materialNames)
{
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		vec3 tempVertex;
		tempVertex.x = mesh->mVertices[i].x;
		tempVertex.y = mesh->mVertices[i].y;
		tempVertex.z = mesh->mVertices[i].z;
		vec2 texCoord(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		vertex v(tempVertex, texCoord, normal);
		m_vertices.push_back(v);

	}

	for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
	{
		aiFace face = mesh->mFaces[j];
		assert(face.mNumIndices == 3);
		m_indices.push_back(face.mIndices[0]);
		m_indices.push_back(face.mIndices[1]);
		m_indices.push_back(face.mIndices[2]);
	}


	logger::trace("parsed model with " + std::to_string(mesh->mNumFaces) + " triangles!");

	for (auto const& positions : m_vertices)
	{
		file << "p " << positions.m_vertex.x << " " << positions.m_vertex.y << " " << positions.m_vertex.z << " " << positions.m_texCoord.x
			<< " " << positions.m_texCoord.y << " " << positions.m_normal.x << " " << positions.m_normal.y << " " << positions.m_normal.z << " " << '\n';
	}
	for (unsigned int i = 0; i < m_indices.size(); i++)
	{
		GLuint index = m_indices[i];
		if (i == 0)
			file << "i ";
		file << index << " ";
	}

	for (auto const& materials : materialNames)
	{
		file << "material " << "assets/materials/" + materials << '\n';
	}

	logger::trace("Model has been converted into binary format!");

	file.close();
	
}

void mesh::loadMeshFromMemory(std::ifstream& file)
{
	int materialIndex = -1;
	int textureIndex = -1;
	for (std::string line; std::getline(file, line);)
	{
		std::istringstream ss(line);
		char dataType;
		ss >> dataType;

		switch (dataType)
		{
		case 'p':
		{
			vec3 positions, normals;
			vec2 texCoords;
			ss >> positions.x >> positions.y >> positions.z >> texCoords.x >> texCoords.y >>
				normals.x >> normals.y >> normals.z;
			m_vertices.push_back(vertex(positions, texCoords, normals));
			break;
		}
		case 'i':
			m_indices = std::vector<GLuint>(std::istream_iterator<GLuint>(ss), std::istream_iterator<GLuint>());
			break;
		case 'm':
		{
			std::string filePath;
			ss >> filePath;
			loadMaterial(filePath.c_str(), materialIndex);
			materialIndex += 3;
			break;
		}
		default:
			break;
		}

	}
	
	file.close();

	loadIntoBuffers(m_vertices, m_indices);
	
}

void mesh::loadMaterial(const char* materialPath, int materialIndex)
{
	m_materials.push_back(new material(materialPath, materialIndex));
}

void mesh::loadIntoBuffers(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<mat4>& translations)
{	
	m_vertexBuffer = new ArrayBuffer();

	m_vertexBuffer->genVao();
	
	m_vertexBuffer->bindVao();
	m_vertexBuffer->loadBuffer(vertices, indices, translations);
	
	m_vertexBuffer->setAttribute(0, 3, GL_FLOAT, sizeof(vertex), (const void*)(0));
	m_vertexBuffer->setAttribute(1, 2, GL_FLOAT, sizeof(vertex), (const void*)(offsetof(vertex, m_texCoord)));
	m_vertexBuffer->setAttribute(2, 3, GL_FLOAT, sizeof(vertex), (const void*)(offsetof(vertex, m_normal)));

	if (!translations.empty())
	{
		int startIndex = 3;
		for (int i = startIndex; i <= startIndex + 3; i++)
		{
			m_vertexBuffer->setAttribute(i, 4, GL_FLOAT, 4 * sizeof(glm::vec4), (GLvoid*)((i - startIndex) * sizeof(glm::vec4)));
			m_vertexBuffer->setAttribDivisor(i, 1);
		}
	}

	m_vertexBuffer->unbindVao();
}
	
void mesh::draw(shaderManager& program)
{
	m_vertexBuffer->bindVao();
	for (auto const& materials : m_materials)
	{
		materials->draw(program);
	}

	m_vertexBuffer->draw();


}

void mesh::drawInstances(shaderManager& program, int count)
{

	for (auto const& materials : m_materials)
	{
		materials->draw(program);
	}

	m_vertexBuffer->bindVao();

	m_vertexBuffer->drawInstances(count);
}

void mesh::clean()
{

	for (auto const& materials : m_materials)
	{
		materials->clean();
		delete materials;
	}

	m_vertexBuffer->clean();
}

std::vector<vertex>& mesh::getVertices()
{
	return m_vertices;
}

std::vector<GLuint>& mesh::getIndices()
{
	return m_indices;
}

std::vector<material*>& mesh::getMaterials()
{
	assert(!m_materials.empty());
	return m_materials;
}

ArrayBuffer* mesh::getVertexBuffer() const 
{
	return m_vertexBuffer;
}