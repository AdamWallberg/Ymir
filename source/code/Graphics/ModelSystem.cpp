#include "ModelSystem.h"
#include "Core.h"
#include "GL.h"
#include <experimental/filesystem>

ModelSystem::ModelSystem()
	: num_models_(0)
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
	std::experimental::filesystem::path p(path);
	if (p.is_relative())
	{
		path = "data/models/" + path;
	}

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

	num_models_++;

	Model* model = newp Model;
	model->id_ = num_models_;
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

		//for (Model* m : model_instances)
		//{
		//	if (m->transform_->parent_ == nullptr)
		//	{
		//		m->transform_->Update();
		//	}
		//}

		struct InstanceData
		{
			pm::mat4 matrix;
			uint id;
			float selected;
		};
		std::vector<InstanceData> instances;
		for (Model* m : model_instances)
		{
			InstanceData data;
			data.matrix = m->transform_->world_matrix_;
			data.id = m->id_;
			data.selected = FLOAT_S(m->selected_);
			instances.push_back(data);
		}

		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceData) * instances.size(), &instances[0], GL_STATIC_DRAW);

		for (uint i = 0; i < raw_model->meshes_.size(); i++)
		{
			uint vao = raw_model->meshes_[i].getVAO();
			glBindVertexArray(vao);

			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)0);
			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(pm::vec4)));
			glEnableVertexAttribArray(7);
			glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(pm::vec4) * 2));
			glEnableVertexAttribArray(8);
			glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(pm::vec4) * 3));
			glEnableVertexAttribArray(9);
			glVertexAttribIPointer(9, 1, GL_UNSIGNED_INT, sizeof(InstanceData), (void*)(sizeof(pm::vec4) * 4));
			glEnableVertexAttribArray(10);
			glVertexAttribPointer(10, 1, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(pm::vec4) * 4 + sizeof(uint)));

			glVertexAttribDivisor(5, 1);
			glVertexAttribDivisor(6, 1);
			glVertexAttribDivisor(7, 1);
			glVertexAttribDivisor(8, 1);
			glVertexAttribDivisor(9, 1);
			glVertexAttribDivisor(10, 1);

			glBindVertexArray(0);
		}
	}
}


SERVICE_LOCATOR_SOURCE(ModelSystem, ModelSystemLocator)