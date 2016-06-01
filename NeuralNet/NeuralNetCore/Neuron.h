#pragma once
#include <random>
#include "Common.h"

class __declspec(dllexport) CNeuron
{
public:
	CNeuron(long numInput);
	virtual ~CNeuron();
	double Run(double* inputData);
	double GetOutput()
	{
		return _output;
	}
	double GetOutputWithoutBias();
	void AddWeight(long iWeight, double weight);
	void AddBias(double bias)
	{
		_bias += bias;
	}
	double GetWeight(long iWeight);
	void SetWeight(long iWeight, double weight);
	void SetBias(double bias)
	{
		_bias = bias;
	}
	double GetBias()
	{
		return _bias;
	}
private:
	long _numInput;
	double* _weight;
	double _bias;
	double _u;
	double _output;
	double Sigmoid(double x, double a = 0.0);
};
