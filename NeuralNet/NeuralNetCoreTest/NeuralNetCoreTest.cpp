#include "stdafx.h"
#include <iostream>
#include <exception>

#define PRINT_TEST_RESULT(testName,x) std::cout<<testName<<(x==true?": successed.":": failed.")<<std::endl

bool Test_CreateNeuralNet()
{
	try
	{
		throw std::exception();
	}
	catch(...)
	{
		return false;
	}

	return true;
}

int main()
{
	PRINT_TEST_RESULT("Test_CreateNeuralNet", Test_CreateNeuralNet());

	getchar();
    return 0;
}

