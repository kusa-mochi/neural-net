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
	// 多層パーセプトロンの層数
	long _numLayer;
	// 各層のニューロン数
	long* _numNeuron;
	// ニューロンの出力
	double** _neuronOutput;
	// 重み係数
	// 各層間で値を持つ。
	double*** _w;
	// バイアス
	// 第2層～出力層の各ニューロン毎に値を持つ。
	double** _bias;
	// 学習係数
	double _learningSpeed1, _learningSpeed2;
	// 重み係数の加算値
	// 各層間で値を持つ。
	double*** _dw;
	// バイアスの加算値
	// 第2層～出力層の各ニューロン毎に値を持つ。
	double** _dbias;
	// 学習信号
	double** _learningSignal;
};
