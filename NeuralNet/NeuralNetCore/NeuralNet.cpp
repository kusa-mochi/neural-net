#include <exception>
#include "NeuralNet.h"

CNeuralNet::CNeuralNet(long numInputDimension, long numOutputDimension, long numLayer, long* numNeuron)
{
	if (numInputDimension < 1)
	{
		throw std::invalid_argument("numInputDimension");
	}
	if (numOutputDimension < 1)
	{
		throw std::invalid_argument("numOutputDimension");
	}
	if (numLayer < 2)
	{
		throw std::invalid_argument("numLayer");
	}
	if (numNeuron == NULL)
	{
		throw std::invalid_argument("numNeuron");
	}
	if (numOutputDimension != numNeuron[numLayer - 1])
	{
		throw std::invalid_argument("numOutputDimension must be same as numNeuron.");
	}

	CNeuralLayer* layer = NULL;
	for (int iLayer = 0; iLayer < numLayer; iLayer++)
	{
		if (layer == NULL)
		{
			layer = new CNeuralLayer(numInputDimension, numNeuron[0]);
		}
		else
		{
			layer->ConnectNextLayer(new CNeuralLayer(layer->GetNumNeuron(), numNeuron[iLayer]));
		}
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
