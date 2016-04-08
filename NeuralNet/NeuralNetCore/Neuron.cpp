#include <iostream>
#include "Neuron.h"



CNeuron::CNeuron()
	: _numInput(0)
	, _weight(NULL)
{
}

CNeuron::CNeuron(long numInput)
{
}

CNeuron::~CNeuron()
{
}


double CNeuron::Run(double* inputData)
{
	return 0.0;
}
