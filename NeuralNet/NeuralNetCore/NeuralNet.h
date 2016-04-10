#pragma once
#include <iostream>
#include <vector>
#include "Neuron.h"

class __declspec(dllexport) CNeuralNet
{
public:
	CNeuralNet(long numInputDimension, long numOutputDimension, long numLayer, long* numNeuron, double learningSpeed);
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
	// �w�K�W��
	double _learningSpeed;
	// �P�񕪂̋��t�f�[�^
	double* _teachData;
	std::vector<std::vector<CNeuron*>> _neurons;
	double Delta(int iLayer, long iNeuron, double teachData = 1.0);
};
