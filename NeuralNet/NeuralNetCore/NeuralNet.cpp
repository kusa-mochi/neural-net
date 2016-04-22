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
	}

	this->GenerateNeuralNet(numInputDimension, numOutputDimension, numLayer, numNeuron, &_neurons);
}

CNeuralNet::~CNeuralNet()
{
	delete[] _numNeuron;
	delete[] _teachData;

	this->DeleteNeurons(&_neurons);
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

	double** output = NULL;
	double d = 0.0;

	// 重み係数を保持しておくためのニューラルネットを生成する。
	std::vector<std::vector<CNeuron*>> tmpNeurons;
	this->GenerateNeuralNet(_numInputDimension, _numOutputDimension, _numLayer, _numNeuron, &tmpNeurons);

	for (long iData = 0L; iData < numData; iData++)
	{
		this->Run(1L, &learnData[iData], &output);

		// 出力層の重み係数更新値を保持する。
		for (long iNeuron = 0L; iNeuron < _numNeuron[_numLayer - 1]; iNeuron++)
		{
			d = this->Delta(_numLayer - 1, iNeuron, teachData[iData][iNeuron]);
			for (long iWeight = 0L; iWeight < _numNeuron[_numLayer - 2]; iWeight++)
			{
				tmpNeurons[_numLayer - 1][iNeuron]->SetWeight(
					iWeight,
					_learningSpeed * d * _neurons[_numLayer - 2][iWeight]->GetOutput()
					);
			}
		}

		// 中間層の重み係数更新値を保持する。
		for (int iLayer = _numLayer - 2; iLayer >= 1; iLayer--)
		{
			for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer]; iNeuron++)
			{
				d = this->Delta(iLayer, iNeuron);
				for (long iWeight = 0L; iWeight < _numNeuron[iLayer - 1]; iWeight++)
				{
					tmpNeurons[iLayer][iNeuron]->SetWeight(
						iWeight,
						_learningSpeed * d * _neurons[iLayer][iWeight]->GetOutput()
						);
				}
			}
		}

		// 入力層の重み係数更新値を保持する。
		for (long iNeuron = 0L; iNeuron < _numNeuron[0]; iNeuron++)
		{
			d = this->Delta(0, iNeuron);
			for (long iWeight = 0L; iWeight < _numInputDimension; iWeight++)
			{
				tmpNeurons[0][iNeuron]->SetWeight(
					iWeight,
					_learningSpeed * d * learnData[iData][iWeight]
					);
			}
		}

		// 重み係数を更新する。
		for (long iNeuron = 0L; iNeuron < _numNeuron[0]; iNeuron++)
		{
			for (long iWeight = 0L; iWeight < _numInputDimension; iWeight++)
			{
				_neurons[0][iNeuron]->AddWeight(
					iWeight,
					tmpNeurons[0][iNeuron]->GetWeight(iWeight)
					);
			}
		}
		for (int iLayer = 1; iLayer < _numLayer; iLayer++)
		{
			for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer]; iNeuron++)
			{
				for (long iWeight = 0L; iWeight < _numNeuron[iLayer - 1]; iWeight++)
				{
					_neurons[iLayer][iNeuron]->AddWeight(
						iWeight,
						tmpNeurons[iLayer][iNeuron]->GetWeight(iWeight)
						);
				}
			}
		}
	}

	// 重み係数の更新値の保持に用いたニューラルネットを破棄する。
	this->DeleteNeurons(&tmpNeurons);
}

long CNeuralNet::GetNumInput()
{
	return _numInputDimension;
}

long CNeuralNet::GetNumOutput()
{
	return _numOutputDimension;
}

long CNeuralNet::GetNumLayer()
{
	return _numLayer;
}

void CNeuralNet::Run(long numData, double** inputData, double*** outputData)
{
	if (numData < 1)
	{
		throw std::invalid_argument("numData");
	}
	if (inputData == NULL)
	{
		throw std::invalid_argument("inputData");
	}
	if (outputData == NULL)
	{
		throw std::invalid_argument("outputData");
	}
	if (_numLayer < 2)
	{
		throw std::exception("_numLayer < 2");
	}

	*outputData = new double*[numData];
	for (int iData = 0L; iData < numData; iData++)
	{
		(*outputData)[iData] = new double[_numOutputDimension];
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

			if (tmpOutput1 != NULL)
			{
				delete[] tmpOutput1;
				tmpOutput1 = NULL;
			}
			tmpOutput1 = tmpOutput2;
		}

		for (long iNeuron = 0L; iNeuron < _numOutputDimension; iNeuron++)
		{
			(*outputData)[iData][iNeuron] = tmpOutput1[iNeuron];
		}
	}

	if (tmpOutput1 != NULL)
	{
		delete[] tmpOutput1;
		tmpOutput1 = NULL;
		tmpOutput2 = NULL;
	}
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

void CNeuralNet::GenerateNeuralNet(long numInputDimension, long numOutputDimension, long numLayer, long* numNeuron, std::vector<std::vector<CNeuron*>>* neurons)
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
	if (neurons == NULL)
	{
		throw std::invalid_argument("neurons");
	}

	for (int iLayer = 0; iLayer < numLayer; iLayer++)
	{
		// 層を追加する。
		neurons->push_back(std::vector<CNeuron*>());

		for (long iNeuron = 0L; iNeuron < numNeuron[iLayer]; iNeuron++)
		{
			// ニューロンを追加する。
			if (iLayer == 0)
			{
				(*neurons)[iLayer].push_back(new CNeuron(numInputDimension));
			}
			else
			{
				(*neurons)[iLayer].push_back(new CNeuron(numNeuron[iLayer - 1]));
			}
		}
	}
}

void CNeuralNet::DeleteNeurons(std::vector<std::vector<CNeuron*>>* neurons)
{
	if (neurons == NULL)
	{
		return;
	}

	for (int iLayer = 0; iLayer < _numLayer; iLayer++)
	{
		for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer]; iNeuron++)
		{
			delete (*neurons)[iLayer][iNeuron];
		}

		(*neurons)[iLayer].clear();
	}
	neurons->clear();
	neurons = NULL;
}
