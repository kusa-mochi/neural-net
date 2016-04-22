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
			// �e��ݒ�
			long NLearn = 100;
			long NTest = 100;
			std::random_device rnd;
			std::mt19937 mt(rnd());
			std::uniform_real_distribution<> x(-10.0, 10.0);
			std::uniform_real_distribution<> y(-10.0, 10.0);
			std::uniform_real_distribution<> xUnder2(-10.0, 2.0);
			std::uniform_real_distribution<> xOver2(2.0, 10.0);

			// �j���[�����l�b�g�𐶐�����B
			CNeuralNet* net = new CNeuralNet(2, 1, 3, new long[3]{ 2, 5, 1 }, 0.3);

			// �w�K�f�[�^�𐶐�����B
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

			// ���t�f�[�^�𐶐�����B
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

			// �w�K����B
			net->Learn(NLearn, learnData, teachData);

			// �e�X�g�f�[�^�𐶐�����B
			double** testData = new double*[NTest];
			for (long iData = 0L; iData < NTest; iData++)
			{
				testData[iData] = new double[2];
				testData[iData][0] = x(mt);
				testData[iData][1] = y(mt);
			}

			// �z�肳���o�͂̃f�[�^�𐶐�����B
			double** targetOutput = new double*[NTest];
			for (long iData = 0L; iData < NTest; iData++)
			{
				targetOutput[iData] = new double[1];
				targetOutput[iData][0] = ((testData[iData][0] > 2.0) ? 1.0 : 0.0);
			}

			// �e�X�g�f�[�^�̓��͂ɑ΂���o�͂𓾂�B
			double** outputData = NULL;
			net->Run(NTest, testData, &outputData);

			// �o�͂�]������B
			std::cout << "input\ttarget\toutput\tscore" << std::endl;
			for (long iData = 0L; iData < NTest; iData++)
			{
				std::cout << "(" << testData[iData][0] << ", " << testData[iData][1] << ")\t" << targetOutput[iData][0] << "\t" << outputData[iData][0] << "\t" << ((((targetOutput[iData][0] - outputData[iData][0]) > -0.1) && ((targetOutput[iData][0] - outputData[iData][0]) < 0.1)) ? 1 : 0) << std::endl;
			}
		}
	};
}