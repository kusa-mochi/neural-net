#pragma once
class __declspec(dllexport) CNeuron
{
public:
	CNeuron(long numInput);
	virtual ~CNeuron();
	double Run(double* inputData);
	double GetOutput();
	void AddWeight(long iWeight, double weight);
	double GetWeight(long iWeight);
private:
	long _numInput;
	double* _weight;
	double _bias;
	double _output;
	double Sigmoid(double x, double a = 1.0);
};
