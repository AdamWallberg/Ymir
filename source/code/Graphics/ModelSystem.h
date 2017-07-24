#pragma once

#include "Types.h"
#include <string>
#include <map>
#include <vector>

class RawModel;
class Model;

class ModelSystem
{
public:
	ModelSystem();
	~ModelSystem();

	Model* loadModel(std::string path);
	std::map<RawModel*, std::pair<uint, std::vector<Model>>>& getModels() { return models_; }
	void updateInstanceBuffers();
private:
	std::map<RawModel*, std::pair<uint, std::vector<Model>>> models_;
};