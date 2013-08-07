#include <iostream>
#include <time.h>

#include "Matrix44.h"

using namespace std;

int main(int argc, char** argv)
{
	float data[4][4] = { 3.0f, 0.0f, 2.0f, 0.0f,
		                 2.0f, 0.0f, -2.0f, 0.0f,
						 0.0f, 1.0f, 1.0f, 0.0f,
						 0.0f, 0.0f, 0.0f, 1.0f };
	Matrix44 mat(data);

	clock_t start = clock();

	for (unsigned i = 0 ; i < 4096 * 256; ++i)
	{
		Matrix44 inv = mat.Inverse();
	}

	clock_t end = clock();

	cout << "Time Elapsed: " << end - start << endl;

	system("pause");

	return 0;
}