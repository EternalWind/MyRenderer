#include <iostream>
#include <time.h>
#include <math.h>
#include <memory>
#include <vector>

#include "Matrix44.h"
#include "Math.h"
#include "ColorRGBA.h"
#include "Image.h"

using namespace std;

template <size_t size>
class Color
{
public:
	float rgb[size];
};

class ColorRGBA2
{
public:
	ColorRGBA2(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f) 
	{
		rgba[0] = red;
		rgba[1] = green;
		rgba[2] = blue;
		rgba[3] = alpha;
	}

	~ColorRGBA2(void) {}

private:
	float rgba[4];
};

int main(int argc, char** argv)
{
	system("pause");

	return 0;
}