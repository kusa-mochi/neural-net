#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>

#define NUM_UNIT_INPUT 2
#define NUM_UNIT_HIDDEN 3
#define NUM_UNIT_OUTPUT 1
#define NUM_LEARN_PATTERN 4
#define NUM_TEST_PATTERN NUM_LEARN_PATTERN
#define NUM_LEARN 100000
#define LEARN_SPEED1 0.8
#define LEARN_SPEED2 0.75
#define MAX_RAND 0.30
#define MIN_RAND -0.30

#define URAND() (((double)rand() / (0x7fff * (MAX_RAND - MIN_RAND))) + MIN_RAND)

double out_in[NUM_LEARN_PATTERN][NUM_UNIT_INPUT], out_hid[NUM_UNIT_HIDDEN], out_out[NUM_UNIT_OUTPUT];
double witoh[NUM_UNIT_HIDDEN][NUM_UNIT_INPUT], whtoo[NUM_UNIT_OUTPUT][NUM_UNIT_HIDDEN];
double hbias[NUM_UNIT_HIDDEN], obias[NUM_UNIT_OUTPUT];

double tsignal[NUM_LEARN_PATTERN][NUM_UNIT_OUTPUT];
double dwitoh[NUM_UNIT_HIDDEN][NUM_UNIT_INPUT], dwhtoo[NUM_UNIT_OUTPUT][NUM_UNIT_HIDDEN];
double dhbias[NUM_UNIT_HIDDEN], dobias[NUM_UNIT_OUTPUT];
double dwho[NUM_UNIT_OUTPUT], dwih[NUM_UNIT_HIDDEN];

#ifdef _DEBUG
std::ofstream fs;
#endif

double Sigmoid(double x, double a = 0.0)
{
	return (1.0 / (1.0 + exp(a - x)));
}

void InitParams()
{
	srand((unsigned)time(NULL));

	out_in[0][0] = 0.0;
	out_in[0][1] = 0.0;
	out_in[1][0] = 1.0;
	out_in[1][1] = 0.0;
	out_in[2][0] = 0.0;
	out_in[2][1] = 1.0;
	out_in[3][0] = 1.0;
	out_in[3][1] = 1.0;

	tsignal[0][0] = 0.0;
	tsignal[1][0] = 1.0;
	tsignal[2][0] = 1.0;
	tsignal[3][0] = 0.0;

	for (int i = 0; i < NUM_UNIT_HIDDEN; i++)
	{
		for (int j = 0; j < NUM_UNIT_INPUT; j++)
		{
			witoh[i][j] = URAND();
		}
	}

	for (int i = 0; i < NUM_UNIT_OUTPUT; i++)
	{
		for (int j = 0; j < NUM_UNIT_HIDDEN; j++)
		{
			whtoo[i][j] = URAND();
		}
	}
}

void LearnNeuralNet(int pattern)
{
	double sum = 0.0;

	for (int i = 0; i < NUM_UNIT_OUTPUT; i++)
	{
		dwho[i] = (tsignal[pattern][i] - out_out[i]) * out_out[i] * (1.0 - out_out[i]);
	}
	for (int i = 0; i < NUM_UNIT_HIDDEN; i++)
	{
		sum = 0.0;
		for (int j = 0; j < NUM_UNIT_OUTPUT; j++)
		{
			dwhtoo[j][i] = LEARN_SPEED1 * dwho[j] * out_hid[i] + LEARN_SPEED2 * dwhtoo[j][i];
			whtoo[j][i] += dwhtoo[j][i];
			sum += dwho[j] * whtoo[j][i];
		}
		dwih[i] = out_hid[i] * (1.0 - out_hid[i]) * sum;
	}
	for (int i = 0; i < NUM_UNIT_OUTPUT; i++)
	{
		dobias[i] = LEARN_SPEED1 * dwho[i] + LEARN_SPEED2 * dobias[i];
		obias[i] += dobias[i];
	}
	for (int i = 0; i < NUM_UNIT_INPUT; i++)
	{
		for (int j = 0; j < NUM_UNIT_HIDDEN; j++)
		{
			dwitoh[j][i] = LEARN_SPEED1 * dwih[j] * out_in[pattern][i] + LEARN_SPEED2 * dwitoh[j][i];
			witoh[j][i] += dwitoh[j][i];
		}
	}
	for (int i = 0; i < NUM_UNIT_HIDDEN; i++)
	{
		dhbias[i] = LEARN_SPEED1 * dwih[i] + LEARN_SPEED2 * dhbias[i];
		hbias[i] += dhbias[i];
	}
}

void RunNeuralNet(int pattern)
{
	double sum = 0.0;

	for (int i = 0; i < NUM_UNIT_HIDDEN; i++)
	{
		sum = 0.0;
		for (int j = 0; j < NUM_UNIT_INPUT; j++)
		{
			sum += witoh[i][j] * out_in[pattern][j];
		}
		sum += hbias[i];
		out_hid[i] = Sigmoid(sum);
	}

	for (int i = 0; i < NUM_UNIT_OUTPUT; i++)
	{
		sum = 0.0;
		for (int j = 0; j < NUM_UNIT_HIDDEN; j++)
		{
			sum += whtoo[i][j] * out_hid[j];
		}
		sum += obias[i];
		out_out[i] = Sigmoid(sum);
	}
}

#ifdef _DEBUG
void DebugPrint()
{
	for (int i = 0; i < NUM_UNIT_HIDDEN; i++)
	{
		for (int j = 0; j < NUM_UNIT_INPUT; j++)
		{
			fs << witoh[i][j] << ", ";
		}
	}

	for (int i = 0; i < NUM_UNIT_OUTPUT; i++)
	{
		for (int j = 0; j < NUM_UNIT_HIDDEN; j++)
		{
			fs << whtoo[i][j] << ",";
		}
	}

	for (int i = 0; i < NUM_UNIT_HIDDEN; i++)
	{
		fs << hbias[i] << ", ";
	}

	for (int i = 0; i < NUM_UNIT_OUTPUT; i++)
	{
		fs << obias[i] << ", ";
	}

	fs << std::endl;
}

void OpenFile()
{
	fs.open("c:\\tmp\\result.csv");
}

void CloseFile()
{
	fs.close();
}
#endif

int main()
{
	InitParams();

#ifdef _DEBUG
	OpenFile();
#endif

	for (long iLearn = 0L; iLearn < NUM_LEARN; iLearn++)
	{
		for (int iPattern = 0; iPattern < NUM_LEARN_PATTERN; iPattern++)
		{
			RunNeuralNet(iPattern);
			LearnNeuralNet(iPattern);
#ifdef _DEBUG
			DebugPrint();
#endif
		}
	}

	for (int iPattern = 0; iPattern < NUM_TEST_PATTERN; iPattern++)
	{
		RunNeuralNet(iPattern);
		std::cout << "test pattern: " << iPattern << ", target: " << tsignal[iPattern][0] << ", result: " << out_out[0] << std::endl;
	}

#ifdef _DEBUG
	CloseFile();
#endif

	getchar();

	return 0;
}
