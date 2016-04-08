#pragma once

#include <iostream>

class CNeuralLayer
{
public:
	CNeuralLayer(long numInput, long numOutput, CNeuralLayer* pPrevLayer = NULL, CNeuralLayer* pNextLayer = NULL);
	virtual ~CNeuralLayer();
	void Run(double* outputData);
private:
	long _numInput;
	long _numNeuron;
	CNeuralLayer* _pPrevLayer;
	CNeuralLayer* _pNextLayer;
public:
	void AdjustNeurons();
	void SetInputs(double* inputData);
	void SetPrevLayer(CNeuralLayer* pPrevLayer);
	void SetNextLayer(CNeuralLayer* pNextLayer);
	void ConnectNextLayer(CNeuralLayer* pNextLayer);
	long GetNumNeuron();
};
