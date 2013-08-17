#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <memory>
#include <vector>

#include "Matrix44.h"
#include "Math.h"
#include "ColorRGBA.h"
#include "Image.h"
#include "Camera.h"

using namespace std;

int main(int argc, char** argv)
{
	shared_ptr<Image> img(new Image(640, 480));
	Camera cam(img);
	cam.SetFOV(M_PI / 3);

	cam.Render();

	img->SaveAsPPM("TestCamera3.ppm");

	system("pause");

	return 0;
}