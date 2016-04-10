#include <iostream>
#include "Neuron.h"

CNeuron::CNeuron(long numInput)
	: _output(0.0)
{
	if (numInput < 1)
	{
		throw std::invalid_argument("numInput");
	}

	_numInput = numInput;
	_weight = new double[numInput];
}

CNeuron::~CNeuron()
{
	delete[] _weight;
}


double CNeuron::Run(double* inputData)
{
	double sum = 0.0;
	for (long iInput = 0L; iInput < _numInput; iInput++)
	{
		sum += _weight[iInput] * inputData[iInput];
	}

	_output = this->Sigmoid(sum + _bias, 1.0);
	return _output;
}


double CNeuron::Sigmoid(double x, double a)
{
	return 1.0 / (1.0 + std::exp(-a * x));
}


double CNeuron::GetOutput()
{
	return _output;
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