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
#include "Sphere.h"
#include "Disk.h"

using namespace std;

int main(int argc, char** argv)
{
	Ray r(Vector3(0.f, 0.f, 1.f), Vector3(0.f, .0f, -1.f));
	AABB box(Vector3(-1.f, -1.f, -1.f), Vector3(1.f, 1.f, 1.f));
	Sphere sphere(Vector3(1.f), 1.f);
	Disk disk(1.f);
	vector<Intersection> intersections;

	bool result = disk.Intersect(r, intersections);

	cout << (result ? "Hit" : "Missed") << endl;

	system("pause");

	return 0;
}