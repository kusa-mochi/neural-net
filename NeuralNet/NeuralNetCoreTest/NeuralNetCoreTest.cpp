#include "stdafx.h"
#include <iostream>
#include <exception>
#include <cassert>
#include <time.h>
#include "NeuralNetCore.h"

#define MAX_RAND 1.0
#define MIN_RAND -1.0
#define URAND() (((double)rand() / (0x7fff * (MAX_RAND - MIN_RAND))) + MIN_RAND)

void DoTest(std::string testName, bool(*pFunc)())
{
	std::cout << "tesing " << testName.c_str() << "...";
	std::cout << (pFunc() == true ? ": successed." : ": failed.") << std::endl;
}

////XXXのテスト
//bool Test_XXXX()
//{
//	try
//	{
//		assert(true);
//	}
//	catch (...)
//	{
//		return false;
//	}
//
//	return true;
//}

// ニューラルネット生成のテスト
bool Test_CreateNeuralNet()
{
	long* numNeuron = NULL;
	CNeuralNetCore* net = NULL;

	try
	{
		numNeuron = new long[3]{ 2, 2, 1 };
		net = new CNeuralNetCore(3, numNeuron);
	}
	catch (...)
	{
		delete[] numNeuron;
		delete net;
		return false;
	}

	delete[] numNeuron;
	delete net;
	return true;
}

//学習のテスト
bool Test_Learn_XOR()
{
	double* testData1 = new double[2]{ 0.0, 0.0 };
	double* testData2 = new double[2]{ 0.0, 1.0 };
	double* testData3 = new double[2]{ 1.0, 0.0 };
	double* testData4 = new double[2]{ 1.0, 1.0 };
	double* teachData1 = new double[1]{ 0.4 };
	double* teachData2 = new double[1]{ 1.0 };
	double* teachData3 = new double[1]{ 0.2 };
	double* teachData4 = new double[1]{ 0.1234567 };
	CNeuralNetCore* net = NULL;
	long numLayer = 4;
	long* numNeuron = new long[4]{ 2, 3, 3, 1 };
	double* result = new double[1];

	try
	{
		// 各種設定
		long NLearn = 100000;

		// ニューラルネットを生成する。
		net = new CNeuralNetCore(numLayer, numNeuron);

		// 学習する。
		for (long iLearn = 0L; iLearn < NLearn; iLearn++)
		{
			net->Learn(testData1, teachData1);
			net->Learn(testData2, teachData2);
			net->Learn(testData3, teachData3);
			net->Learn(testData4, teachData4);
		}

		// テストデータの入力に対する出力を得る。
		std::cout << std::endl;
		net->Run(testData1, result); std::cout << "{0.0, 0.0} => " << result[0] << std::endl;
		net->Run(testData2, result); std::cout << "{0.0, 1.0} => " << result[0] << std::endl;
		net->Run(testData3, result); std::cout << "{1.0, 0.0} => " << result[0] << std::endl;
		net->Run(testData4, result); std::cout << "{1.0, 1.0} => " << result[0] << std::endl;
	}
	catch (...)
	{
		delete[] testData1;
		delete[] testData2;
		delete[] testData3;
		delete[] testData4;
		delete[] teachData1;
		delete[] teachData2;
		delete[] teachData3;
		delete[] teachData4;
		delete net;
		delete[] numNeuron;
		delete[] result;
		return false;
	}

	delete net;
	delete[] numNeuron;
	delete[] result;
	return true;
}

// 判別のテスト
bool Test_HiLow()
{
	CNeuralNetCore* net = NULL;
	long numLayer = 3;
	long* numNeuron = new long[3]{ 1, 3, 1 };
	double* result = new double[1];
	double* testData = new double[1]{ 0.0 };
	double* teachData = new double[1]{ 0.0 };
	long NLearn = 10000;
	long NTest = 10;

	try
	{
		net = new CNeuralNetCore(numLayer, numNeuron);
		for (long iLearn = 0L; iLearn < NLearn; iLearn++)
		{
			testData[0] = URAND();
			if (testData[0] < -0.7)
			{
				teachData[0] = 0.0;
			}
			else
			{
				teachData[0] = 1.0;
			}

			net->Learn(testData, teachData);
		}

		std::cout << std::endl;
		for (long iTest = 0L; iTest < NTest; iTest++)
		{
			testData[0] = URAND();
			if (testData[0] < -0.7)
			{
				teachData[0] = 0.0;
			}
			else
			{
				teachData[0] = 1.0;
			}

			net->Run(testData, result);
			std::cout << iTest << "| data: " << testData[0] << ", target: " << teachData[0] << ", result: " << result[0] << std::endl;
		}
	}
	catch (...)
	{
		delete net;
		delete[] numNeuron;
		delete[] result;
		delete[] testData;
		delete[] teachData;
		return false;
	}

	delete net;
	delete[] numNeuron;
	delete[] result;
	delete[] testData;
	delete[] teachData;
	return true;
}

int main()
{
	srand((unsigned int)time(NULL));

	DoTest("Test_CreateNeuralNet", Test_CreateNeuralNet);
	DoTest("Test_Learn_XOR", Test_Learn_XOR);
	DoTest("Test_HiLow", Test_HiLow);

	getchar();
	return 0;
}

