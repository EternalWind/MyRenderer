#include <iostream>
#include <time.h>
#include <math.h>
#include <memory>
#include <vector>

#include "Matrix44.h"
#include "Math.h"
#include "ColorRGBA.h"

using namespace std;

class Color
{
public:
	inline void SetR(float val) { r = val; }
	inline void SetG(float val) { g = val; }
	inline void SetB(float val) { b = val; }
	inline void SetA(float val) { a = val; }

	float r;
	float g;
	float b;
	float a;
};

int main(int argc, char** argv)
{
	unsigned count = 1920 * 1080;
	clock_t start = clock();
	clock_t end, time1, time2, time3;

	Vector<5> qwe;
	auto v = qwe.ElementAt(3);

	auto w = Math::Clamp(1.5, 1., 0.);

	ColorRGBA* array1 = (ColorRGBA*)malloc(count * sizeof(ColorRGBA));

	for (unsigned i = 0; i < count; ++i)
	{
		array1[i].SetRed(10);
		array1[i].SetGreen(532);
		array1[i].SetBlue(24);
		array1[i].SetAlpha(1);
	}

	end = clock();
	time1 = end - start;
	start = clock();

	float* array2 = new float[count * 4];
	unsigned index = 0;

	for (unsigned i = 0; i < count; ++i)
	{
		index = i * 4;

		array2[index] = 10;
		array2[index + 1] = 532;
		array2[index + 2] = 24;
		array2[index + 3] = 1;
	}

	end = clock();
	time2 = end - start;
	start = clock();

	Color* array3 = new Color[count];
	
	for (unsigned i = 0; i < count; ++i)
	{
		array3[i].SetR(10);
		array3[i].SetG(532);
		array3[i].SetB(24);
		array3[i].SetA(1);
	}

	end = clock();
	time3 = end - start;

	cout << "Time Elapsed" << endl;
	cout << "ColorRGBA: " << time1 << endl;
	cout << "float: " << time2 << endl;
	cout << "Color: " << time3 << endl;

	system("pause");

	return 0;
}