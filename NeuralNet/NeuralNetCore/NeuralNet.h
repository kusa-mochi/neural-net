#pragma once
#include <iostream>
#include "NeuralLayer.h"

class CNeuralNet
{
public:
	CNeuralNet();
	CNeuralNet(long numInputDimension, long numOutputDimension, long numLayer, long* numNeuron);
	virtual ~CNeuralNet();
	void Learn(long numData, double** learnData, double** teachData);
	void Run(long numData, double** inputData, double** outputData);
private:
	// ���̓f�[�^�̎�����
	long _numInputDimension;
	// �o�̓f�[�^�̎�����
	long _numOutputDimension;
	// ���w�p�[�Z�v�g�����̑w��
	long _numLayer;
	// �e�w�̃j���[������
	long* _numNeuron;
	CNeuralLayer* _layers;
};
