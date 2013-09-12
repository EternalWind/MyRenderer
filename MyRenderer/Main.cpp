#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <memory>
#include <vector>
#include <random>
#include <list>
#include <array>

#include "Matrix44.h"
#include "Math.h"
#include "ColorRGBA.h"
#include "Image.h"
#include "Camera.h"
#include "AABB.h"
#include "Ray.h"
#include "Sphere.h"
#include "Disk.h"
#include "RayTracer.h"
#include "Scene.h"
#include "Triangle.h"
#include "PolygonGenerator.h"
#include "BezierCurve.h"

#include "teapotdata.h"

using namespace std;

int main(int argc, char** argv)
{
	clock_t start1, start2, start3, end1, end2, end3;

	start1 = clock();
	shared_ptr<Renderer> renderer(new RayTracer());
	shared_ptr<Image> image(new Image(640, 480));
	shared_ptr<Scene> scene = renderer->AddScene(shared_ptr<Scene>(new Scene(ColorRGBA(0.f, 0.f, 0.f))));
	shared_ptr<Camera> cam = scene->AddCamera(shared_ptr<Camera>(new Camera(image, Vector3(0.f, 0.f, 3.f))));
	cam->SetNearClippingPlane(.1f);
	cam->SetFarClippingPlane(100.f);

	float data1[4][4] = {
		{ 1.f, 0.f, 0.f, 0.f },
		{ 0.f, cos(M_PI / 2), -sin(M_PI / 2), 0.0f },
		{ 0.f, sin(M_PI / 2), cos(M_PI / 2), 0.0f },
		{ 0.f, 0.f, 0.f, 1.f } };

	float data2[4][4] = {
		{ 1.f, 0.f, 0.f, 0.f },
		{ 0.f, 1.f, 0.f, 0.f },
		{ 0.f, 0.f, 1.f, 1.0f },
		{ 0.f, 0.f, 0.f, 1.f } };

	Matrix44 trans1(data1);
	Matrix44 trans2(data2);

	cam->Transform(trans1);
	cam->Transform(trans2);

	const unsigned divs = 4;

	for (unsigned p = 0; p < kTeapotNumPatches; ++p)
	{
		BezierSurface<4, 4> patch;
		unsigned* patch_data = teapotPatches[p];

		for (unsigned i = 0; i < 4; ++i)
			for (unsigned j = 0; j < 4; ++j)
			{
				unsigned index = i * 4 + j;

				patch.SetControlPoint(i, j, Vector3(
					teapotVertices[patch_data[index]][0],
					teapotVertices[patch_data[index]][1],
					teapotVertices[patch_data[index]][2]));
			}

			scene->AddGeometry(PolygonGenerator::Surface(patch, divs));
	}

	//scene->AddGeometry(PolygonGenerator::Sphere(1.f, 10));

	//renderer->AsWireFrame(true);
	end1 = clock();

	start2 = clock();
	renderer->Render();
	end2 = clock();

	start3 = clock();
	image->SaveAsPPM("Sphere.ppm");
	end3 = clock();

	cout << "Init: " << end1 - start1 << endl;
	cout << "Render: " << end2 - start2 << endl;
	cout << "Save to disk: " << end3 - start3 << endl;

	/*array<Vector3, 4> cps = { Vector3(-1.f, -1.f), Vector3(-0.5f, 1.f), Vector3(.5f, 1.f), Vector3(1.f, -1.f) };
	BezierCurve<4> curve(cps);

	float t = 0.5f;

	Vector3 p1 = curve.PointAt(t);
	Vector3 p2 = curve.PointAtDCA(t);

	cout << "PointAt(): (" << p1.X() << ", " << p1.Y() << ", " << p1.Z() << ")" << endl;
	cout << "PointAtDCA(): (" << p2.X() << ", " << p2.Y() << ", " << p2.Z() << ")" << endl;*/

	system("pause");

	return 0;
}