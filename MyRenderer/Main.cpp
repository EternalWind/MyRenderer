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

using namespace std;

int main(int argc, char** argv)
{
	clock_t start1, start2, start3, end1, end2, end3;

	start1 = clock();
	shared_ptr<Renderer> renderer(new RayTracer());
	shared_ptr<Image> image(new Image(640, 480));
	shared_ptr<Scene> scene = renderer->AddScene(shared_ptr<Scene>(new Scene(ColorRGBA(0.f, 0.f, 0.f))));
	shared_ptr<Mesh> mesh = PolygonGenerator::Sphere(1.f, 16);

	scene->AddGeometry(mesh);
	shared_ptr<Camera> cam = scene->AddCamera(shared_ptr<Camera>(new Camera(image, Vector3(0.f, 0.f, 2.f))));
	cam->SetNearClippingPlane(.1f);
	cam->SetFarClippingPlane(10.f);

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

	system("pause");

	return 0;
}