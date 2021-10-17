#include "model.h"
#include <cstdio>
#include <fstream>
#include <sstream>
#include <chrono>

namespace corona
{
	namespace objImporter
	{
		static bool importObj(string path, mesh* m, unsigned int flags)				//only use once for converting .obj into .bin					
		{
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			Assimp::Importer importer;

			const aiScene* scene = importer.ReadFile(path, flags);

			if (!scene)
			{
				logger::error(importer.GetErrorString());
				return false;
			}

			auto it = path.find(".obj");
			if (it == string::npos)
				return false;
			path.replace(it, path.length(), ".bin");

			std::ofstream file(path, ios::out | ios::binary | ios::app);

			std::vector<std::string> materialNames;
			for (unsigned int i = 0; i < scene->mNumMaterials; i++)
			{
				aiString matName;
				scene->mMaterials[i]->Get(AI_MATKEY_NAME, matName);
				materialNames.push_back(matName.data);
				
			}

			if (scene->mNumMeshes > 0)
			{
				for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
				{
					aiMesh* tempMesh = scene->mMeshes[i];
					m->writeMeshData(tempMesh, file, materialNames);
				}
			}

			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

			logger::trace("OBJ imported in: " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()) + " in seconds");
			return true;
		}
	}

	model::model(vec3 pos, string name) :
		m_pos{ pos }, m_name{ name }
	{
		m_modelMatrix = glm::mat4(1.0f);
		m_modelMatrix = glm::translate(m_modelMatrix, pos);
	}

	model::model(string name) : m_name{ name }
	{

	}

	bool model::loadModel()
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		std::ifstream file("assets/models/" + m_name + ".bin", ios::in);
		if (!file.is_open())
		{
			logger::error("Failed to load the model's binary file!");
			return false;
		}

		m_modelMesh = new mesh();

		m_modelMesh->loadMeshFromMemory(file);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		logger::trace(m_name + " loaded in " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()) + " seconds!");

		return true;
	}

	void model::importObj()
	{
		m_modelMesh = new mesh();
		objImporter::importObj("assets/models/" + m_name + ".obj", m_modelMesh);
	}


	bool model::loadRawModel(std::vector<vertex>& vertices, std::vector<GLuint>& indices, const char* materialPath)
	{
		logger::trace("loading" + m_name + " raw model!");
		m_modelMesh = new mesh();
		m_modelMesh->loadIntoBuffers(vertices, indices);
		if (materialPath)
			m_modelMesh->loadMaterial(materialPath, 3);

		return true;
	}
	void model::update()
	{
		//	rotate((float)glfwGetTime(), vec3(0.0f, 1.0f, 0.0f));
	}

	void model::translate(vec3 pos)
	{
		m_modelMatrix = glm::translate(m_modelMatrix, pos);
	}

	void model::rotate(float angle, vec3 axis)
	{
		m_modelMatrix = glm::rotate(m_modelMatrix, angle, axis);
	}

	void model::scale(vec3 factor)
	{
		m_modelMatrix = glm::scale(m_modelMatrix, factor);
	}

	void model::identity()
	{
		m_modelMatrix = glm::mat4(1.0f);
	}

	void model::draw(shaderManager& program)
	{
		assert(m_modelMesh && "Mesh not loaded!");

		program.setMatrix4f("model", m_modelMatrix);
		m_modelMesh->draw(program);
		glDisable(GL_BLEND);

	}

	void model::drawInstances(shaderManager& program, int count)
	{
		assert(m_modelMesh && "Mesh not loaded!");
		m_modelMesh->drawInstances(program, count);
	}

	void model::clean()
	{
		assert(m_modelMesh && "Mesh not loaded!");
		m_modelMesh->clean();
		delete m_modelMesh;
	}

	vec3& model::getPos()
	{
		return m_pos;
	}

	string model::getName() const
	{
		return m_name;
	}

	void model::setName(string texId)
	{
		m_name = texId;
	}

	glm::mat4& model::getModel()
	{
		return m_modelMatrix;
	}
}