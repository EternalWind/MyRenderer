#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <memory>
#include <vector>
#include <random>
#include <list>
#include <array>
#include <atomic>

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
#include "Profiler.h"

using namespace std;

int main(int argc, char** argv)
{
	shared_ptr<Renderer> renderer(new RayTracer());
	shared_ptr<Image> image(new Image(640, 480));
	shared_ptr<Scene> scene = renderer->AddScene(shared_ptr<Scene>(new Scene(ColorRGBA(0.f, 0.f, 0.f))));
	shared_ptr<Camera> cam = scene->AddCamera(shared_ptr<Camera>(new Camera(image, Vector3(0.f, 0.f, 5.f))));
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

	MeshGroup meshes = PolygonGenerator::Teapot(16, true);

	for (auto iter = meshes.begin(); iter != meshes.end(); ++iter)
	{
		scene->AddGeometry(*iter);
	}

	//unsigned vp[1] = { 3 };
	//Vector3 v[3] = { Vector3(-1.f, -1.f), Vector3(1.f, -1.f), Vector3(0.f, 1.f) };

	//scene->AddGeometry(shared_ptr<Mesh>(new Mesh(1, vp, v)));

	renderer->Render();

	image->SaveAsPPM("Sphere3.ppm");

	cout << "Profile: " << endl;

	cout << endl;
	cout << endl;

	cout << "Triangles: " << Profiler::numTriangles << endl;
	cout << "Primary Rays Per Frame: " << Profiler::numPrimaryRaysPerFrame << endl;
	cout << "Ray-Triangle Tests Per Frame: " << Profiler::wtf << endl;
	cout << "Intersections Per Frame: " << Profiler::numIntersectionPerFrame << endl;
	cout << endl;
	cout << "Rendering Time Per Frame: " << Profiler::renderTimePerFrame << endl;

	system("pause");

	return 0;
}