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
			// ニューラルネットを生成する。
			CNeuralNet* net = new CNeuralNet(2, 1, 3, new long[3]{ 2, 5, 1 }, 0.3);

			// 学習データを生成する。

			// 教師データを生成する。

			// 学習する。

			// テストデータを生成する。

			// テストデータの入力に対する出力を得る。

			// 出力を評価する。
		}

	};
}