#pragma once
#include <iostream>
#include <exception>
#include <time.h>
#include "Common.h"

#define INPUT_LAYER 0
#define LEARNING_SPEED1 0.8
#define LEARNING_SPEED2 0.75
#define MAX_RAND 0.30
#define MIN_RAND -0.30
#define URAND() (((double)rand() / (0x7fff * (MAX_RAND - MIN_RAND))) + MIN_RAND)
#define SIGMOID(x) (1.0 / (1.0 + exp(-x)))

class __declspec(dllexport) CNeuralNetCore
{
public:
	CNeuralNetCore(long numLayer, long* numNeuron, double learningSpeed1 = LEARNING_SPEED1, double learningSpeed2 = LEARNING_SPEED2);
	virtual ~CNeuralNetCore();
	void Learn(double* learnData, double* teachData);
	void Run(double* inputData, double* outputData = NULL);
private:
	// ���w�p�[�Z�v�g�����̑w��
	long _numLayer;
	// �e�w�̃j���[������
	long* _numNeuron;
	// �j���[�����̏o��
	double** _neuronOutput;
	// �d�݌W��
	// �e�w�ԂŒl�����B
	double*** _w;
	// �o�C�A�X
	// ��2�w�`�o�͑w�̊e�j���[�������ɒl�����B
	double** _bias;
	// �w�K�W��
	double _learningSpeed1, _learningSpeed2;
	// �d�݌W���̉��Z�l
	// �e�w�ԂŒl�����B
	double*** _dw;
	// �o�C�A�X�̉��Z�l
	// ��2�w�`�o�͑w�̊e�j���[�������ɒl�����B
	double** _dbias;
	// �w�K�M��
	double** _learningSignal;
};
