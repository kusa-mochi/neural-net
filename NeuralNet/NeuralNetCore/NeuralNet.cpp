#include <exception>
#include "NeuralNet.h"



CNeuralNet::CNeuralNet()
	: _numInputDimension(0)
	, _numOutputDimension(0)
	, _numLayer(0)
	, _numNeuron(NULL)
	, _layers(NULL)
{
}

CNeuralNet::CNeuralNet(long numInputDimension, long numOutputDimension, long numLayer, long* numNeuron)
{
	if (numInputDimension < 1)
	{
		// TODO
	}
	if (numOutputDimension < 1)
	{
		// TODO
	}
	if (numLayer < 1)
	{
		// TODO
	}
	if (numNeuron == NULL)
	{
		// TODO
	}
}

CNeuralNet::~CNeuralNet()
{
}


void CNeuralNet::Learn(long numData, double** learnData, double** teachData)
{
}


void CNeuralNet::Run(long numData, double** inputData, double** outputData)
{
}
