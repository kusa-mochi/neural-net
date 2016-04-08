#pragma once
class CNeuralLayer
{
public:
	CNeuralLayer();
	virtual ~CNeuralLayer();
	void Run(double* inputData, double* outputData);
private:
	long _numInput;
	long _numNeuron;
};
