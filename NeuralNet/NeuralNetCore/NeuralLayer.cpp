#include "NeuralLayer.h"

CNeuralLayer::CNeuralLayer(long numInput, long numOutput, CNeuralLayer* pPrevLayer = NULL, CNeuralLayer* pNextLayer = NULL)
{
}


CNeuralLayer::~CNeuralLayer()
{
}


void CNeuralLayer::Run(double* outputData)
{
}


void CNeuralLayer::AdjustNeurons()
{
}


void CNeuralLayer::SetInputs(double* inputData)
{
}


void CNeuralLayer::SetPrevLayer(CNeuralLayer* pPrevLayer)
{
}


void CNeuralLayer::SetNextLayer(CNeuralLayer* pNextLayer)
{
}


void CNeuralLayer::ConnectNextLayer(CNeuralLayer* pNextLayer)
{
}


long CNeuralLayer::GetNumNeuron()
{
	return 0;
}
