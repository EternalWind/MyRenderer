#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <memory>
#include <vector>
#include <random>

#include "Matrix44.h"
#include "Math.h"
#include "ColorRGBA.h"
#include "Image.h"
#include "Camera.h"
#include "AABB.h"
#include "Ray.h"

using namespace std;

int main(int argc, char** argv)
{
	Ray r(Vector3(), Vector3(1.f));
	AABB box(Vector3(-1.f, -1.f, -1.f), Vector3(1.f, 1.f, 1.f));

	bool result = box.Intersect(r);

	cout << (result ? "Hit" : "Missed") << endl;

	system("pause");

	return 0;
}