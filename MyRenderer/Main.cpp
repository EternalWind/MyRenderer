#include <iostream>
#include <time.h>

#include "Matrix44.h"
#include "Math.h"

using namespace std;

int main(int argc, char** argv)
{
	float a = .5f;
	float b = .0f;

	cout << Math::Clamp(a, 1.f, .0f) << endl;

	system("pause");

	return 0;
}