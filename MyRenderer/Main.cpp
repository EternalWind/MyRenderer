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

using namespace std;

template <size_t size>
class Base
{
public:
   //~Base() {}
	virtual void WTF() = 0;

protected:
	float m_Elements[size];
};

struct V3 : public Base<3>
{
	V3() {}
	V3(float a, float b, float c) { m_Elements[0] = a; m_Elements[1] = b; m_Elements[2] = c; }
	//~V3() {}
	void WTF() {}

	void SetX(float x) { m_Elements[0] = x; }
	void SetY(float x) { m_Elements[1] = x; }
	void SetZ(float x) { m_Elements[2] = x; }
};

int main(int argc, char** argv)
{
	shared_ptr<Renderer> renderer(new RayTracer());
	shared_ptr<Image> image(new Image(640, 480));
	shared_ptr<Scene> scene = renderer->AddScene(shared_ptr<Scene>(new Scene(ColorRGBA(0.f, 0.f, 0.f))));
	scene->AddGeometry(shared_ptr<IIntersectTarget>(new Triangle(new Vector3(-0.5f, -0.5f, 0.0f), new Vector3(0.5f, -0.5f, 0.f), new Vector3(0.f, 0.5f, 0.f))));
	shared_ptr<Camera> cam = scene->AddCamera(shared_ptr<Camera>(new Camera(image, Vector3(0.f, 0.f, 2.f))));
	cam->SetNearClippingPlane(.1f);
	cam->SetFarClippingPlane(10.f);

	renderer->Render();

	image->SaveAsPPM("FirstBlood.ppm");

	system("pause");

	return 0;
}