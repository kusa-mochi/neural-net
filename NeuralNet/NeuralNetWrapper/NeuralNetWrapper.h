// NeuralNetWrapper.h

#pragma once
#include "../NeuralNetCore/NeuralNetCore.h"

using namespace System;

namespace NeuralNetWrapper {

	public ref class NeuralNet
	{
	private:
		CNeuralNetCore* net;
	public:
		NeuralNet(array<long>^ numNeuron)
		{
			pin_ptr<long> p = &numNeuron[0];
			net = new CNeuralNetCore(numNeuron->LongLength, p);
		}

		~NeuralNet()
		{
			delete net;
		}

		void Learn(array<double>^ learnData, array<double>^ teachData)
		{
			pin_ptr<double> ptrLearnData = &learnData[0];
			pin_ptr<double> ptrTeachData = &teachData[0];
			net->Learn(ptrLearnData, ptrTeachData);
		}

		void Run(array<double>^ inputData, array<double>^ outputData)
		{
			pin_ptr<double> ptrInputData = &inputData[0];
			pin_ptr<double> ptrOutputData = &outputData[0];
			net->Run(ptrInputData, ptrOutputData);
		}
	};
}
