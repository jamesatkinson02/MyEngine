#pragma once
#include "GL/glew.h"
#include "glm.hpp"
#include <string>
#include <vector>
#include "shaderManager.h"
#include "material.h"
#include "scene.h"
#include "mesh.h"
#include "Importer.hpp"
#include "postprocess.h"
using namespace glm;
using namespace std;

namespace corona
{
	namespace objImporter
	{
		static bool importObj(string path, mesh* m, unsigned int flags= aiProcess_FlipUVs | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);				//only use once for converting .obj into .bin					
	}

	class model
	{
	protected:
		vec3 m_pos;
		string m_name;
		string m_currentMaterialName;
		mesh* m_modelMesh;
		vector<mesh*> m_meshes;
	private:
		glm::mat4& getModel();
		glm::mat4 m_modelMatrix;
	public:
		model(vec3 pos, string name);
		model(string name);
		virtual bool loadModel();
		bool loadRawModel(std::vector<vertex>& vertices, std::vector<GLuint>& indices, const char* materialPath = 0);
		vec3& getPos();
		string getName() const;
		void setName(string name);
		void update();
		virtual void rotate(float angle, vec3 axis);
		virtual void translate(vec3 pos);
		virtual void identity();
		virtual void scale(vec3 factor);
		virtual void draw(shaderManager& program);
		virtual void drawInstances(shaderManager& program, int count);
		virtual void clean();
		void importObj();
	};
}

