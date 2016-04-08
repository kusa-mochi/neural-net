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
	// 入力データの次元数
	long _numInputDimension;
	// 出力データの次元数
	long _numOutputDimension;
	// 多層パーセプトロンの層数
	long _numLayer;
	// 各層のニューロン数
	long* _numNeuron;
	CNeuralLayer* _layers;
};
