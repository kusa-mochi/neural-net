#include "stdafx.h"
#include <random>
#include "CppUnitTest.h"
#include "../NeuralNetCore/NeuralNet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NeuralNetCoreTest
{
	TEST_CLASS(UnitTest_NeuralNet)
	{
	public:

		TEST_METHOD(Test_GenerateNeuralNet)
		{
			CNeuralNet* net = new CNeuralNet(2, 1, 3, new long[3]{ 2, 5, 1 }, 0.3);
			long numInput = net->GetNumInput();
			long numOutput = net->GetNumOutput();
			long numLayer = net->GetNumLayer();

			Assert::AreEqual(numInput, 2L);
			Assert::AreEqual(numOutput, 1L);
			Assert::AreEqual(numLayer, 3L);
		}

		TEST_METHOD(Test_XY_X_OVER_2)
		{
			// 各種設定
			long NLearn = 100;
			long NTest = 100;
			std::random_device rnd;
			std::mt19937 mt(rnd());
			std::uniform_real_distribution<> x(-10.0, 10.0);
			std::uniform_real_distribution<> y(-10.0, 10.0);
			std::uniform_real_distribution<> xUnder2(-10.0, 2.0);
			std::uniform_real_distribution<> xOver2(2.0, 10.0);

			// ニューラルネットを生成する。
			CNeuralNet* net = new CNeuralNet(2, 1, 3, new long[3]{ 2, 5, 1 }, 0.3);

			// 学習データを生成する。
			double** learnData = new double*[NLearn];
			for (long iData = 0L; iData < NLearn; iData++)
			{
				learnData[iData] = new double[2];
				if (iData % 2 == 0)
				{
					learnData[iData][0] = xUnder2(mt);
					learnData[iData][1] = y(mt);
				}
				else
				{
					learnData[iData][0] = xOver2(mt);
					learnData[iData][1] = y(mt);
				}
			}

			// 教師データを生成する。
			double** teachData = new double*[NLearn];
			for (long iData = 0L; iData < NLearn; iData++)
			{
				teachData[iData] = new double[1];
				if (iData % 2 == 0)
				{
					teachData[iData][0] = 0.0;
				}
				else
				{
					teachData[iData][0] = 1.0;
				}
			}

			// 学習する。
			net->Learn(NLearn, learnData, teachData);

			// テストデータを生成する。
			double** testData = new double*[NTest];
			for (long iData = 0L; iData < NTest; iData++)
			{
				testData[iData] = new double[2];
				testData[iData][0] = x(mt);
				testData[iData][1] = y(mt);
			}

			// 想定される出力のデータを生成する。
			double** targetOutput = new double*[NTest];
			for (long iData = 0L; iData < NTest; iData++)
			{
				targetOutput[iData] = new double[1];
				targetOutput[iData][0] = ((testData[iData][0] > 2.0) ? 1.0 : 0.0);
			}

			// テストデータの入力に対する出力を得る。
			double** outputData = NULL;
			net->Run(NTest, testData, &outputData);

			// 出力を評価する。
			std::cout << "input\ttarget\toutput\tscore" << std::endl;
			for (long iData = 0L; iData < NTest; iData++)
			{
				std::cout << "(" << testData[iData][0] << ", " << testData[iData][1] << ")\t" << targetOutput[iData][0] << "\t" << outputData[iData][0] << "\t" << ((((targetOutput[iData][0] - outputData[iData][0]) > -0.1) && ((targetOutput[iData][0] - outputData[iData][0]) < 0.1)) ? 1 : 0) << std::endl;
			}
		}
	};
}