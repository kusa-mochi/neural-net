#pragma once
class CNeuron
{
public:
	CNeuron();
	CNeuron(long numInput);
	virtual ~CNeuron();
	double Run(double* inputData);
private:
	long _numInput;
	double* _weight;
};
