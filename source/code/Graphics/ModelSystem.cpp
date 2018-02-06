#include "ModelSystem.h"
#include "Core.h"
#include "GL.h"

ModelSystem::ModelSystem()
{
}

ModelSystem::~ModelSystem()
{
	for (auto& it : models_)
	{
		for (Model* m : it.second.second)
		{
			delete m;
		}
		delete it.first;
	}
}

Model* ModelSystem::loadModel(std::string path)
{
	path = "data/models/" + path;

	RawModel* raw_model = nullptr;
	for (auto& it : models_)
	{
		RawModel* raw_model_iterator = it.first;
		if (path == raw_model_iterator->path_)
		{
			raw_model = raw_model_iterator;
			break;
		}
	}
	
	if (!raw_model)
	{
		raw_model = newp RawModel(path);
		glGenBuffers(1, &models_[raw_model].first);
	}

	Model* model = newp Model;
	models_[raw_model].second.push_back(model);

	return model;
}

void ModelSystem::updateInstanceBuffers()
{
	for (auto& it : models_)
	{
		RawModel* raw_model = it.first;
		uint& buffer_id = it.second.first;
		std::vector<Model*>& model_instances = it.second.second;

		for (Model* m : model_instances)
		{
			if (m->transform_->parent_ == nullptr)
			{
				m->transform_->Update();
			}
		}

		std::vector<pm::mat4> matrices;
		for (Model* m : model_instances)
		{
			matrices.push_back(m->transform_->world_matrix_);
		}

		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pm::mat4) * matrices.size(), &matrices[0].elements[0], GL_STATIC_DRAW);

		for (uint i = 0; i < raw_model->meshes_.size(); i++)
		{
			uint vao = raw_model->meshes_[i].getVAO();
			glBindVertexArray(vao);

			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(pm::mat4), (void*)0);
			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(pm::mat4), (void*)(sizeof(pm::vec4)));
			glEnableVertexAttribArray(7);
			glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(pm::mat4), (void*)(sizeof(pm::vec4) * 2));
			glEnableVertexAttribArray(8);
			glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(pm::mat4), (void*)(sizeof(pm::vec4) * 3));

			glVertexAttribDivisor(5, 1);
			glVertexAttribDivisor(6, 1);
			glVertexAttribDivisor(7, 1);
			glVertexAttribDivisor(8, 1);

			glBindVertexArray(0);
		}
	}
}


SERVICE_LOCATOR_SOURCE(ModelSystem, ModelSystemLocator)