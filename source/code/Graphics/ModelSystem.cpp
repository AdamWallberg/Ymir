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

	Model model;
	model.transform = pm::mat4(1.0f);
	models_[raw_model].second.push_back(model);

	return &models_[raw_model].second[models_[raw_model].second.size() - 1];
}

void ModelSystem::updateInstanceBuffers()
{
	for (auto& it : models_)
	{
		RawModel* raw_model = it.first;
		uint& buffer_id = it.second.first;
		std::vector<Model>& model_instances = it.second.second;

		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Model) * model_instances.size(), &model_instances[0], GL_STATIC_DRAW);

		for (uint i = 0; i < raw_model->meshes_.size(); i++)
		{
			uint vao = raw_model->meshes_[i].getVAO();
			glBindVertexArray(vao);

			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Model), (void*)0);
			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Model), (void*)(sizeof(pm::vec4)));
			glEnableVertexAttribArray(7);
			glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Model), (void*)(sizeof(pm::vec4) * 2));
			glEnableVertexAttribArray(8);
			glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(Model), (void*)(sizeof(pm::vec4) * 3));

			glVertexAttribDivisor(5, 1);
			glVertexAttribDivisor(6, 1);
			glVertexAttribDivisor(7, 1);
			glVertexAttribDivisor(8, 1);

			glBindVertexArray(0);
		}
	}
}


SERVICE_LOCATOR_SOURCE(ModelSystem, ModelSystemLocator)