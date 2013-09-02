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
#include "RayTracer.h"
#include "Scene.h"
#include "Triangle.h"

class A
{
public:
	virtual void Func() const = 0;
	virtual ~A() = 0 {}
};

class B : public A
{
public:
	void Func() const {}
	~B() {}
};

using namespace std;

int main(int argc, char** argv)
{
	shared_ptr<Renderer> renderer(new RayTracer());
	shared_ptr<Image> image(new Image(640, 480));
	shared_ptr<Scene> scene = renderer->AddScene(shared_ptr<Scene>(new Scene(ColorRGBA(0.f, 0.f, 0.f))));
	scene->AddGeometry(shared_ptr<IIntersectTarget>(new Triangle(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.f), Vector3(0.f, 0.5f, 0.f))));
	shared_ptr<Camera> cam = scene->AddCamera(shared_ptr<Camera>(new Camera(image, Vector3(0.f, 0.f, 2.f))));
	cam->SetNearClippingPlane(.1f);
	cam->SetFarClippingPlane(10.f);

	renderer->Render();

	image->SaveAsPPM("FirstBlood.ppm");

	system("pause");

	return 0;
}