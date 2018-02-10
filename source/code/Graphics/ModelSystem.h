#pragma once

#include "Types.h"
#include <string>
#include <map>
#include <vector>
#include "RawModel.h"
#include "Model.h"

class ModelSystem
{
public:
	ModelSystem();
	~ModelSystem();

	Model* loadModel(std::string path);
	std::map<RawModel*, std::pair<uint, std::vector<Model*>>>& getModels() { return models_; }
	void updateInstanceBuffers();
private:
	std::map<RawModel*, std::pair<uint, std::vector<Model*>>> models_;
	uint num_models_;
};

#include "ServiceLocator.h"
SERVICE_LOCATOR_HEADER(ModelSystem, ModelSystemLocator)