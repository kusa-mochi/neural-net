#include "stdafx.h"
#include "CppUnitTest.h"
#include "../NeuralNetCore/NeuralNet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NeuralNetCoreTest
{
	TEST_CLASS(UnitTest_NeuralNet)
	{
	public:

		TEST_METHOD(Test_XY_X_OVER_2)
		{
			// �j���[�����l�b�g�𐶐�����B
			CNeuralNet* net = new CNeuralNet(2, 1, 3, new long[3]{ 2, 5, 1 }, 0.3);

			// �w�K�f�[�^�𐶐�����B

			// ���t�f�[�^�𐶐�����B

			// �w�K����B

			// �e�X�g�f�[�^�𐶐�����B

			// �e�X�g�f�[�^�̓��͂ɑ΂���o�͂𓾂�B

			// �o�͂�]������B
		}

	};
}