#include <iostream>
#include "Neuron.h"

CNeuron::CNeuron(long numInput)
	: _output(0.0)
{
	if (numInput < 1)
	{
		throw std::invalid_argument("numInput");
	}

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<> weightRandValue(0, 1.0);

	_numInput = numInput;
	_bias = weightRandValue(mt);
	_weight = new double[numInput];
	for (long iWeight = 0L; iWeight < numInput; iWeight++)
	{
		_weight[iWeight] = weightRandValue(mt);
	}
}

CNeuron::~CNeuron()
{
	delete[] _weight;
}


double CNeuron::Run(double* inputData)
{
	_u = 0.0;
	for (long iInput = 0L; iInput < _numInput; iInput++)
	{
		_u += _weight[iInput] * inputData[iInput];
	}

	_output = this->Sigmoid(_u - _bias, 1.0);
	return _output;
}


double CNeuron::GetOutputWithoutBias()
{
	return this->Sigmoid(_u, 1.0);
}


double CNeuron::Sigmoid(double x, double a)
{
	return 1.0 / (1.0 + std::exp(-a * x));
}


void CNeuron::AddWeight(long iWeight, double dWeight)
{
	if ((iWeight < 0) || (_numInput <= iWeight))
	{
		throw std::invalid_argument("iWeight");
	}
	if (_weight == NULL)
	{
		throw std::exception("_weight == NULL");
	}

	_weight[iWeight] += dWeight;
}


double CNeuron::GetWeight(long iWeight)
{
	if ((iWeight < 0) || (_numInput <= iWeight))
	{
		throw std::invalid_argument("iWeight");
	}
	if (_weight == NULL)
	{
		throw std::exception("_weight == NULL");
	}

	return _weight[iWeight];
}


void CNeuron::SetWeight(long iWeight, double weight)
{
	if ((iWeight < 0) || (_numInput <= iWeight))
	{
		throw std::invalid_argument("iWeight");
	}
	if (_weight == NULL)
	{
		throw std::exception("_weight == NULL");
	}

	_weight[iWeight] = weight;
}