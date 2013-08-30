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

using namespace std;

int main(int argc, char** argv)
{
	shared_ptr<Renderer> renderer(new RayTracer());
	shared_ptr<Image> image(new Image(640, 480));
	shared_ptr<Scene> scene = renderer->AddScene(shared_ptr<Scene>(new Scene(ColorRGBA(0.f, 0.f, 0.f))));
	////shared_ptr<IIntersectTarget> sphere1 = scene->AddGeometry(shared_ptr<IIntersectTarget>(new Sphere(Vector3(), 1.f, ColorRGBA(1.f, 0.f, 0.f))));	
	////shared_ptr<IIntersectTarget> sphere2 = scene->AddGeometry(shared_ptr<IIntersectTarget>(new Sphere(Vector3(.5f, .5f, -0.2f), 1.f, ColorRGBA(0.f, 1.f, 0.f))));	
	scene->AddGeometry(shared_ptr<IIntersectTarget>(new Triangle(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.f), Vector3(0.f, 0.5f, 0.f))));
	////scene->AddGeometry(shared_ptr<IIntersectTarget>(new Triangle(Vector3(0.2f, 0.f, 0.2f), Vector3(1.5f, 0.f, -1.5f), Vector3(0.2f, 1.f, 0.2f), ColorRGBA(1.f))));
	////scene->AddGeometry(shared_ptr<IIntersectTarget>(new Disk(1.f, Vector3(), Vector3(0.f, 0.f, 1.f), ColorRGBA(1.f, 0.f, 0.f))));
	////scene->AddGeometry(shared_ptr<IIntersectTarget>(new Disk(1.f, Vector3(0.f, 1.f, -.5f), Vector3(0.f, 0.f, 1.f), ColorRGBA(0.f, 1.f, 0.f))));
	shared_ptr<Camera> cam = scene->AddCamera(shared_ptr<Camera>(new Camera(image, Vector3(0.f, 0.f, 2.f))));
	cam->SetNearClippingPlane(.1f);
	cam->SetFarClippingPlane(10.f);

	renderer->Render();

	/*for (unsigned i = 0; i < 480; ++i)
		for (unsigned j = 0; j < 640; ++j)
		{
			if (i > 200 && i < 400)
			{
				if (j > 300 && j < 500)
				{
					float c1 = (i - 200.f) / 200.f;

					image->SetPixel(i, j, ColorRGBA(c1, 1.f, 0.0f));
				}
			}
		}*/

	image->SaveAsPPM("FirstBlood.ppm");

	system("pause");

	return 0;
}