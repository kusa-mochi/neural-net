#include "NeuralNetCore.h"

CNeuralNetCore::CNeuralNetCore(long numLayer, long* numNeuron, double learningSpeed1, double learningSpeed2)
{
	if (numLayer < 3) throw std::invalid_argument("numLayer must be over 2.");
	if (numNeuron == NULL) throw std::invalid_argument("numNeuron");
	if (learningSpeed1 < 0.0) throw std::invalid_argument("learningSpeed1");
	if (learningSpeed2 < 0.0) throw std::invalid_argument("learningSpeed2");

	_numLayer = numLayer;
	_numNeuron = new long[_numLayer];
	_neuronOutput = new double*[_numLayer];
	for (long iLayer = 0L; iLayer < _numLayer; iLayer++)
	{
		_numNeuron[iLayer] = numNeuron[iLayer];
		_neuronOutput[iLayer] = new double[_numNeuron[iLayer]];
	}

	_learningSpeed1 = learningSpeed1;
	_learningSpeed2 = learningSpeed2;

	srand((unsigned int)time(NULL));

	_w = new double**[_numLayer - 1];
	_dw = new double**[_numLayer - 1];
	_bias = new double*[_numLayer - 1];
	_dbias = new double*[_numLayer - 1];
	_learningSignal = new double*[_numLayer - 1];
	for (long iLayer = 0L; iLayer < _numLayer - 1; iLayer++)
	{
		_w[iLayer] = new double*[_numNeuron[iLayer + 1]];
		_dw[iLayer] = new double*[_numNeuron[iLayer + 1]];
		_bias[iLayer] = new double[_numNeuron[iLayer + 1]];
		_dbias[iLayer] = new double[_numNeuron[iLayer + 1]];
		_learningSignal[iLayer] = new double[_numNeuron[iLayer + 1]];
		for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer + 1]; iNeuron++)
		{
			_w[iLayer][iNeuron] = new double[_numNeuron[iLayer]];
			_dw[iLayer][iNeuron] = new double[_numNeuron[iLayer]];
			_bias[iLayer][iNeuron] = URAND();
			_dbias[iLayer][iNeuron] = 0.0;
			_learningSignal[iLayer][iNeuron] = 0.0;
			for (long iWeight = 0L; iWeight < _numNeuron[iLayer]; iWeight++)
			{
				_w[iLayer][iNeuron][iWeight] = URAND();
				_dw[iLayer][iNeuron][iWeight] = 0.0;
			}
		}
	}
}

CNeuralNetCore::~CNeuralNetCore()
{
	delete [] _numNeuron;
	for (long iLayer = 0L; iLayer < _numLayer; iLayer++)
	{
		delete [] _neuronOutput[iLayer];
	}
	delete [] _neuronOutput;

	
	for (long iLayer = 0L; iLayer < _numLayer - 1; iLayer++)
	{
		
		for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer + 1]; iNeuron++)
		{
			delete[] _w[iLayer][iNeuron];
			delete[] _dw[iLayer][iNeuron];
		}
		delete[] _w[iLayer];
		delete[] _dw[iLayer];
		delete[] _bias[iLayer];
		delete[] _dbias[iLayer];
		delete[] _learningSignal[iLayer];
	}
	delete[] _w;
	delete[] _dw;
	delete[] _bias;
	delete[] _dbias;
	delete[] _learningSignal;
}

void CNeuralNetCore::Learn(double* learnData, double* teachData)
{
	if (learnData == NULL) throw std::invalid_argument("learnData");
	if (teachData == NULL) throw std::invalid_argument("teachData");

	double sum = 0.0;

	this->Run(learnData);

	for (long iNeuron = 0L; iNeuron < _numNeuron[_numLayer - 1]; iNeuron++)
	{
		_learningSignal[_numLayer - 2][iNeuron] = (teachData[iNeuron] - _neuronOutput[_numLayer - 1][iNeuron])
			* _neuronOutput[_numLayer - 1][iNeuron]
			* (1.0 - _neuronOutput[_numLayer - 1][iNeuron]);
	}

	for (long iLayer = _numLayer - 1; iLayer >= 1; iLayer--)
	{
		for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer - 1]; iNeuron++)
		{
			sum = 0.0;
			for (long jNeuron = 0L; jNeuron < _numNeuron[iLayer]; jNeuron++)
			{
				_dw[iLayer - 1][jNeuron][iNeuron] = LEARNING_SPEED1 * _learningSignal[iLayer - 1][jNeuron] * _neuronOutput[iLayer - 1][iNeuron] + LEARNING_SPEED2 * _dw[iLayer - 1][jNeuron][iNeuron];
				_w[iLayer - 1][jNeuron][iNeuron] += _dw[iLayer - 1][jNeuron][iNeuron];
				sum += _learningSignal[iLayer - 1][jNeuron] * _w[iLayer - 1][jNeuron][iNeuron];
			}
			if (iLayer >= 2)
			{
				_learningSignal[iLayer - 2][iNeuron] = _neuronOutput[iLayer - 1][iNeuron] * (1.0 - _neuronOutput[iLayer - 1][iNeuron]) * sum;
			}
		}
	}

	for (long iLayer = _numLayer - 1; iLayer >= 1; iLayer--)
	{
		for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer]; iNeuron++)
		{
			_dbias[iLayer - 1][iNeuron] = LEARNING_SPEED1 * _learningSignal[iLayer - 1][iNeuron] + LEARNING_SPEED2 * _dbias[iLayer - 1][iNeuron];
			_bias[iLayer - 1][iNeuron] += _dbias[iLayer - 1][iNeuron];
		}
	}
}

// outputDataに結果を出力する場合は，本関数呼び出し前にoutputDataのメモリ領域を確保しておくこと。
void CNeuralNetCore::Run(double* inputData, double* outputData)
{
	if (inputData == NULL)
	{
		throw std::invalid_argument("inputData");
	}

	// outputDataに出力する場合はtrue
	bool fOutput = true;

	if (outputData == NULL)
	{
		// 結果を出力しない設定とする。
		fOutput = false;
	}

	if (_numLayer < 3)
	{
		throw std::exception("_numLayer < 3");
	}

	double sum = 0.0;

	for (long iNeuron = 0; iNeuron < _numNeuron[INPUT_LAYER]; iNeuron++)
	{
		_neuronOutput[0][iNeuron] = inputData[iNeuron];
	}

	for (long iLayer = 1L; iLayer < _numLayer; iLayer++)
	{
		for (long iNeuron = 0L; iNeuron < _numNeuron[iLayer]; iNeuron++)
		{
			sum = 0.0;
			for (long iWeight = 0L; iWeight < _numNeuron[iLayer - 1]; iWeight++)
			{
				sum += _w[iLayer - 1][iNeuron][iWeight] * _neuronOutput[iLayer - 1][iWeight];
			}
			sum += _bias[iLayer - 1][iNeuron];
			_neuronOutput[iLayer][iNeuron] = SIGMOID(sum);
		}
	}

	if (fOutput == true)
	{
		// 結果をoutputDataに出力する。
		for (long iNeuron = 0L; iNeuron < _numNeuron[_numLayer - 1]; iNeuron++)
		{
			outputData[iNeuron] = _neuronOutput[_numLayer - 1][iNeuron];
		}
	}
}
