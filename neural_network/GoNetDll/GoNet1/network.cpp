#include "network.h"

#include <windows.h>

typedef std::pair<std::wstring, std::vector<ElemType>*> MapEntry;
typedef std::map<std::wstring, std::vector<ElemType>*> Layer;

// Used for retrieving the model appropriate for the element type (float / double)
template<typename ElemType>
using GetEvalProc = void(*)(Microsoft::MSR::CNTK::IEvaluateModel<ElemType>**);

Network::Network(const std::string& model_file_path)
{
	auto hModule = LoadLibrary(L"Evaldll.dll");
	if (!hModule)
		throw std::runtime_error("unable to load dll");

	//auto procAddress = GetProcAddress(hModule, "GetEvalD");
	auto procAddress = GetProcAddress(hModule, "GetEvalF");
	auto getEvalProc = (GetEvalProc<ElemType>)procAddress;
	getEvalProc(&m_model);

	if (!m_model)
		throw std::runtime_error("unable to load evaluation");

	m_model->CreateNetwork("modelPath=\"" + model_file_path + "\"");
}

Network::~Network()
{
	if (m_model) m_model->Destroy();
}

std::vector<ElemType> Network::forward(std::vector<ElemType> inputs)
{
	std::map<std::wstring, size_t> inDims;
	std::map<std::wstring, size_t> outDims;
	m_model->GetNodeDimensions(inDims, Microsoft::MSR::CNTK::NodeGroup::nodeInput);
	m_model->GetNodeDimensions(outDims, Microsoft::MSR::CNTK::NodeGroup::nodeOutput);

	auto inputLayerName = inDims.begin()->first;
	const auto nb_input = inDims[inputLayerName];

	if (inputs.size() != nb_input)
		throw std::runtime_error("Invalid input vector");

	std::vector<ElemType> outputs;
	Layer inputLayer;
	inputLayer.insert(MapEntry(inputLayerName, &inputs));
	Layer outputLayer;
	auto outputLayerName = outDims.begin()->first;
	outputLayer.insert(MapEntry(outputLayerName, &outputs));

	m_model->Evaluate(inputLayer, outputLayer);
	return outputs;
}
