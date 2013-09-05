#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <memory>
#include <vector>
#include <random>
#include <list>

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

using namespace std;

class Base
{
public:
   //~Base() {}
	virtual void WTF() = 0;

protected:
	Base() {}

	Base(const Base& other) {}

	//Base operator = (const Base& other) { return nullptr; }

	//float m_Elements[size];
};

class V3 : public Base
{
public:
	void WTF() {}
};

int main(int argc, char** argv)
{
	shared_ptr<Renderer> renderer(new RayTracer());
	shared_ptr<Image> image(new Image(640, 480));
	shared_ptr<Scene> scene = renderer->AddScene(shared_ptr<Scene>(new Scene(ColorRGBA(0.f, 0.f, 0.f))));
	scene->AddGeometry(PolygonGenerator::Sphere(1.f, 3));
	shared_ptr<Camera> cam = scene->AddCamera(shared_ptr<Camera>(new Camera(image, Vector3(0.f, 0.f, 2.f))));
	cam->SetNearClippingPlane(.1f);
	cam->SetFarClippingPlane(10.f);

	renderer->Render();

	image->SaveAsPPM("Sphere.ppm");

	system("pause");

	return 0;
}