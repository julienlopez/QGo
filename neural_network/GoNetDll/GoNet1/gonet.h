#pragma once

extern "C"
{

	int __declspec(dllexport) createNet(const char* filename);
	void __declspec(dllexport) releaseNet();

	/**
	* @pre pixels is a 19*19 long float array
	* @pre res is a 19*19 long float array
	*/
	int __declspec(dllexport) analyze(const float* const pixels, float* res);

}
