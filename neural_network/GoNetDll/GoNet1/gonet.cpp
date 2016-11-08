#include "network.h"

#include <cassert>
#include <iostream>

static Network* s_network = 0;

extern "C" int __declspec(dllexport) createNet(const char* filename)
{
	try
	{
		s_network = new Network(filename);
		return 1;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return 0;
	}
}

extern "C" void __declspec(dllexport) releaseNet()
{
	delete s_network;
}

extern "C" int __declspec(dllexport) analyze(const float* const pixels, float* res)
{
	try
	{
		assert(pixels);
		assert(res);
		std::vector<float> inputs(pixels, pixels + 19 * 19);
		const auto outputs = s_network->forward(inputs);
		assert(outputs.size() == 19 * 19);
		std::copy(outputs.begin(), outputs.end(), res);
		return 1;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception : " << ex.what() << std::endl;
		std::fill(res, res + 19 * 19, 0.f);
		return 0;
	}
}