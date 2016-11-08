#pragma once

#include "Eval.h"

using ElemType = float;

class Network
{
public:
	Network(const std::string& model_file_path);

	~Network();


	std::vector<ElemType> forward(std::vector<ElemType> inputs);

private:
	// Native model evaluation instance
	Microsoft::MSR::CNTK::IEvaluateModel<ElemType>* m_model = nullptr;
};