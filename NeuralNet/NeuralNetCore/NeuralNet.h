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
	// 入力データの次元数
	long _numInputDimension;
	// 出力データの次元数
	long _numOutputDimension;
	// 多層パーセプトロンの層数
	long _numLayer;
	// 各層のニューロン数
	long* _numNeuron;
	// 学習係数
	double _learningSpeed;
	// １回分の教師データ
	double* _teachData;
	std::vector<std::vector<CNeuron*>> _neurons;
	double Delta(int iLayer, long iNeuron, double teachData = 1.0);
};
