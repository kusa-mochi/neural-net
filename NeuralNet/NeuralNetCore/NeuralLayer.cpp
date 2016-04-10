//#include "NeuralLayer.h"
//
//CNeuralLayer::CNeuralLayer(long numInput, long numOutput)
//	: _inputData(NULL)
//	, _outputData(NULL)
//	, _neurons(NULL)
//{
//	if (numInput < 1)
//	{
//		throw std::invalid_argument("numInput");
//	}
//	if (numOutput < 1)
//	{
//		throw std::invalid_argument("numOutput");
//	}
//
//	_numInput = numInput;
//	_numOutput = numOutput;
//	_inputData = new double[numInput];
//	_outputData = new double[numOutput];
//	for (long iNeuron = 0L; iNeuron < numOutput; iNeuron++)
//	{
//		_neurons.push_back(new CNeuron(numInput));
//	}
//}
//
//
//CNeuralLayer::~CNeuralLayer()
//{
//	for (int iNeuron = 1; iNeuron < _numOutput; iNeuron++)
//	{
//		delete _neurons[iNeuron];
//	}
//	_neurons.clear();
//}
//
//
//void CNeuralLayer::Run(CNeuralLayer* nextLayer = NULL)
//{
//	if (_inputData == NULL)
//	{
//		throw std::exception("_inputData == NULL");
//	}
//
//	delete[] _outputData;
//	_outputData = new double[_numOutput];
//
//	for (long iNeuron = 0L; iNeuron < _numOutput; iNeuron++)
//	{
//		_outputData[iNeuron] = _neurons[iNeuron]->Run(_inputData);
//	}
//
//	if (nextLayer != NULL)
//	{
//		nextLayer->SetInputs(_outputData);
//	}
//}
//
//
//void CNeuralLayer::AdjustNeurons()
//{
//}
//
//
//void CNeuralLayer::SetInputs(double* inputData)
//{
//	if (inputData == NULL)
//	{
//		throw std::invalid_argument("inputData");
//	}
//
//	delete[] _inputData;
//	_inputData = new double[_numInput];
//	for (long iInput = 0L; iInput < _numInput; iInput++)
//	{
//		_inputData[iInput] = inputData[iInput];
//	}
//}
//
//
//long CNeuralLayer::GetNumNeuron()
//{
//	return _numOutput;
//}
//
//
//void CNeuralLayer::GetOutput(double* outputData)
//{
//	delete[] outputData;
//	outputData = new double[_numOutput];
//	for (long iNeuron = 0L; iNeuron < _numOutput; iNeuron++)
//	{
//		outputData[iNeuron] = _outputData[iNeuron];
//	}
//}
