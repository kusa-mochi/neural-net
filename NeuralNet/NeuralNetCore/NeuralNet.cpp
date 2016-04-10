#include <exception>
#include "NeuralNet.h"

CNeuralNet::CNeuralNet(long numInputDimension, long numOutputDimension, long numLayer, long* numNeuron, double learningSpeed)
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
		throw std::invalid_argument("numLayer must be over 1.");
	}
	if (numNeuron == NULL)
	{
		throw std::invalid_argument("numNeuron");
	}
	if (numOutputDimension != numNeuron[numLayer - 1])
	{
		throw std::invalid_argument("numOutputDimension must be same as numNeuron.");
	}
	if (learningSpeed < 0.0)
	{
		throw std::invalid_argument("learningSpeed");
	}

	_numInputDimension = numInputDimension;
	_numOutputDimension = numOutputDimension;
	_numLayer = numLayer;
	_numNeuron = new long[numLayer];
	_learningSpeed = learningSpeed;
	_teachData = NULL;
	for (int iLayer = 0; iLayer < numLayer; iLayer++)
	{
		_numNeuron[iLayer] = numNeuron[iLayer];

		// 層を追加する。
		_neurons.push_back(std::vector<CNeuron*>());

		for (long iNeuron = 0L; iNeuron < numNeuron[iLayer]; iNeuron++)
		{
			// ニューロンを追加する。
			if (iLayer == 0)
			{
				_neurons[iLayer].push_back(new CNeuron(_numNeuron[0]));
			}
			else if (iLayer == _numLayer - 1)
			{
				_neurons[iLayer].push_back(new CNeuron(numOutputDimension));
			}
			else
			{
				_neurons[iLayer].push_back(new CNeuron(_neurons[iLayer - 1].size()));
			}
		}
	}
}

CNeuralNet::~CNeuralNet()
{
	delete[] _numNeuron;
	delete[] _teachData;

	for (int iLayer = 0; iLayer < _numLayer; iLayer++)
	{
		for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer]; iNeuron++)
		{
			delete _neurons[iLayer][iNeuron];
		}
		_neurons[iLayer].clear();
	}
	_neurons.clear();
}

void CNeuralNet::Learn(long numData, double** learnData, double** teachData)
{
	if (numData < 1)
	{
		throw std::invalid_argument("numData");
	}
	if (learnData == NULL)
	{
		throw std::invalid_argument("learnData");
	}
	if (teachData == NULL)
	{
		throw std::invalid_argument("teachData");
	}

	_teachData = new double[_numOutputDimension];

	double* output = new double[_numOutputDimension];
	double d = 0.0;
	for (long iData = 0L; iData < numData; iData++)
	{
		this->Run(1L, &learnData[iData], &output);

		// 出力層の重み係数更新
		for (long iNeuron = 0L; iNeuron < _numNeuron[_numLayer - 1]; iNeuron++)
		{
			d = this->Delta(_numLayer - 1, iNeuron, teachData[iData][iNeuron]);
			for (long iWeight = 0L; iWeight < _numNeuron[_numLayer - 2]; iWeight++)
			{
				_neurons[_numLayer - 1][iNeuron]->AddWeight(
					iWeight,
					_learningSpeed * d * _neurons[_numLayer - 2][iWeight]->GetOutput()
					);
			}
		}

		// 中間層の重み係数更新
		for (int iLayer = _numLayer - 2; iLayer >= 1; iLayer--)
		{
			for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer]; iNeuron++)
			{
				d = this->Delta(iLayer, iNeuron);
				for (long iWeight = 0L; iWeight < _numNeuron[iLayer - 1]; iWeight++)
				{
					_neurons[iLayer][iNeuron]->AddWeight(
						iWeight,
						_learningSpeed * d * _neurons[iLayer][iWeight]->GetOutput()
						);
				}
			}
		}

		// 入力層の重み係数更新
		for (long iNeuron = 0L; iNeuron < _numNeuron[0]; iNeuron++)
		{
			d = this->Delta(0, iNeuron);
			for (long iWeight = 0L; iWeight < _numInputDimension; iWeight++)
			{
				_neurons[0][iNeuron]->AddWeight(
					iWeight,
					_learningSpeed * d * learnData[iData][iWeight]
					);
			}
		}
	}
}

void CNeuralNet::Run(long numData, double** inputData, double** outputData)
{
	if (numData < 1)
	{
		throw std::invalid_argument("numData");
	}
	if (inputData == NULL)
	{
		throw std::invalid_argument("inputData");
	}
	if (outputData != NULL)
	{
		throw std::invalid_argument("outputData");
	}
	if (_numLayer < 2)
	{
		throw std::exception("_numLayer < 2");
	}

	outputData = new double*[numData];
	for (int iData = 0L; iData < numData; iData++)
	{
		outputData[iData] = new double[_numOutputDimension];
	}

	double* tmpOutput1 = NULL;
	double* tmpOutput2 = NULL;
	for (long iData = 0L; iData < numData; iData++)
	{
		tmpOutput1 = new double[_numNeuron[0]];
		for (long iNeuron = 0L; iNeuron < _numNeuron[0]; iNeuron++)
		{
			tmpOutput1[iNeuron] = _neurons[0][iNeuron]->Run(inputData[iData]);
		}
		for (int iLayer = 1L; iLayer < _numLayer; iLayer++)
		{
			tmpOutput2 = new double[_numNeuron[iLayer]];
			for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer]; iNeuron++)
			{
				tmpOutput2[iNeuron] = _neurons[iLayer][iNeuron]->Run(tmpOutput1);
			}

			delete tmpOutput1;
			tmpOutput1 = tmpOutput2;
		}

		for (long iNeuron = 0L; iNeuron < _numOutputDimension; iNeuron++)
		{
			outputData[iData][iNeuron] = tmpOutput1[iNeuron];
		}
	}

	delete tmpOutput1;
	delete tmpOutput2;
}


double CNeuralNet::Delta(int iLayer, long iNeuron, double teachData)
{
	if ((iLayer < 0) || (_numLayer <= iLayer))
	{
		throw std::invalid_argument("iLayer");
	}
	if (_numNeuron == NULL)
	{
		throw std::exception("_numNeuron == NULL");
	}
	if ((iNeuron < 0) || (_numNeuron[iLayer] <= iNeuron))
	{
		throw std::invalid_argument("iNeuron");
	}

	double delta = 0.0;
	double output = _neurons[iLayer][iNeuron]->GetOutput();

	if (iLayer == _numLayer - 1)
	{
		delta = (teachData - output) * output * (1.0 - output);
	}
	else
	{
		for (long iNextNeuron = 0L; iNextNeuron < _numNeuron[iLayer + 1]; iNextNeuron++)
		{
			delta += _neurons[iLayer + 1][iNextNeuron]->GetWeight(iNeuron) * this->Delta(iLayer + 1, iNextNeuron);
		}
		delta *= output * (1.0 - output);
	}

	return delta;
}
