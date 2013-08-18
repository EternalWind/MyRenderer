//#include <iostream>
//#include <fstream>
//#include <time.h>
//#include <math.h>
//#include <memory>
//#include <vector>
//
#include "Matrix44.h"
#include "Math.h"
#include "ColorRGBA.h"
#include "Image.h"
#include "Camera.h"

//using namespace std;
//
//int main(int argc, char** argv)
//{
//	clock_t start = clock();
//	shared_ptr<Image> img(new Image(640, 480));
//	Camera cam(img);
//	cam.SetFOV(M_PI / 3);
//
//	cam.Render();
//
//	//img->SaveAsPPM("TestCamera3.ppm");
//
//	clock_t end = clock();
//
//	cout << "Time Elapsed: " << end - start << endl;
//
//	system("pause");
//
//	return 0;
//}

/*
	LRT
	Copyright (C) 2012  www.scratchapixel.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <time.h>

#include <cmath>
#include <limits>

#include <fstream>
#include <iostream>

#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

template<typename T>
class Vec3
{
public:
	Vec3() {}
	Vec3(T xx) : x(xx), y(xx), z(xx) {}
	Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
	Vec3 operator - (const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
	T dot(const Vec3<T> &v) const { return x * v.x + y * v.y + z * v.z; }
	T& operator [] (size_t i) { return (&x)[i]; }
	T operator [] (size_t i) const { return (&x)[i]; }
	T x, y, z;
};

void normalize(Vec3<float> &v)
{
	float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len > 0) {
		float invLen = 1 / len;
		v.x *= invLen, v.y *= invLen, v.z *= invLen;
	}
}

template<typename T>
class Matrix44X
{
public:
	T m[4][4];
	Matrix44X()
	{
		m[0][0] = T(1.0);
		m[0][1] = T(0.0);
		m[0][2] = T(0.0);
		m[0][3] = T(0.0);
		m[1][0] = T(0.0);
		m[1][1] = T(1.0);
		m[1][2] = T(0.0);
		m[1][3] = T(0.0);
		m[2][0] = T(0.0);
		m[2][1] = T(0.0);
		m[2][2] = T(1.0);
		m[2][3] = T(0.0);
		m[3][0] = T(0.0);
		m[3][1] = T(0.0);
		m[3][2] = T(0.0);
		m[3][3] = T(1.0);
	}
	const T* operator [] (size_t i) const { return &m[i][0]; }
	T* operator [] (size_t i) { return &m[i][0]; }
	static const Matrix44X<T> Identity;
	// transform a point in homogeneous form (see OpenExr lib)
	template<typename S>
	void multVecMatrix(const Vec3<S> &src, Vec3<S> &dst) const
	{
		S x = src[0] * m[0][0] + src[1] * m[1][0] + src[2] * m[2][0] + m[3][0];
		S y = src[0] * m[0][1] + src[1] * m[1][1] + src[2] * m[2][1] + m[3][1];
		S z = src[0] * m[0][2] + src[1] * m[1][2] + src[2] * m[2][2] + m[3][2];
		S w = src[0] * m[0][3] + src[1] * m[1][3] + src[2] * m[2][3] + m[3][3];
		dst[0] = x / w;
		dst[1] = y / w;
		dst[2] = z / w;
	}
	// we are just interested in rotations. Use the 3x3 sub-matrix
	template<typename S>
	void multDirMatrix(const Vec3<S> &src, Vec3<S> &dst) const
	{
		dst[0] = src[0] * m[0][0] + src[1] * m[1][0] + src[2] * m[2][0];
		dst[1] = src[0] * m[0][1] + src[1] * m[1][1] + src[2] * m[2][1];
		dst[2] = src[0] * m[0][2] + src[1] * m[1][2] + src[2] * m[2][2];
	}
	friend std::ostream & operator << (std::ostream &os, const Matrix44X<T> &m)
	{
		os << "[";
		os.precision(7);
		const T *c = &m[0][0];
		for (size_t i = 0; i < 16; ++i) {
			os << *(c++) << ((i==15) ? "]" : " ");
		}
		return os;
	}
};

template<typename T>
const Matrix44X<T> Matrix44X<T>::Identity;

template<typename T>
class Ray
{
public:
	Ray() : tmin(0), tmax(std::numeric_limits<T>::max()) {}
	Ray(const Vec3<T> &o, const Vec3<T> &d) : orig(o), dir(d), tmin(0), tmax(std::numeric_limits<T>::max()) {}
	Vec3<T> orig, dir;
	mutable T tmin, tmax;
};

class Vector32
{
public:
	Vector32() {}

	Vector32(float x, float y, float z) :
		x(x),
		y(y),
		z(z)
	{
	}

	float X() const { return x; }

	float Y() const { return y; }

	float Z() const { return z; }

	void SetX(float x) { this->x = x; }

	void SetY(float y) { this->y = y; }

	void SetZ(float z) { this->z = z; }

	~Vector32(void) {}

protected:
	float x, y, z;
};


int main(int argc, char **argv)
{
	clock_t start1 = clock();
	//unsigned width = 640, height = 480;
	//unsigned char *buffer = new unsigned char [width * height * 3], *pix = buffer;
	//memset(buffer, 0x0, sizeof(unsigned char) * width * height);
	//float focal = 60;
	//float angle = tan(focal * 0.5 * M_PI / 180); // convert from degree to radian
	//float imageAspectRatio = float(width) / height;
	//// loop over all the pixels of the image
	//Vector3 rayOrigin;
	//Matrix44 cameraToWorld;
	//cameraToWorld.Multiply(Vector3(), rayOrigin);
	//for (unsigned j = 0; j < height; ++j) {
	//	for (unsigned i = 0; i < width; ++i, pix += 3) {
	//		// remap from raster to screen space
	//		float xx = (2 * (i + 0.5) / width - 1) * angle * imageAspectRatio;
	//		float yy = (1 - 2 * (j + 0.5) / height) * angle;

	//		// create the ray direction, looking down the z-axis
	//		// and transform by the camera-to-world matrix
	//		Vector3 rayDirection;
	//		cameraToWorld.Multiply(Vector3(xx, yy, -1), rayDirection);
	//		rayDirection.Normalise();

	//		//Ray<float> ray(rayOrigin, rayDirection);

	//		// convert the ray direction to a color
	//		pix[0] = (unsigned char)(255 * (1 + rayDirection.X()) * 0.5);
	//		pix[1] = (unsigned char)(255 * (1 + rayDirection.Y()) * 0.5);
	//		pix[2] = 0;
	//	}
	//}
	//// save to PPM
	///*std::ofstream ofs;
	//ofs.open("./untitled.ppm");
	//ofs << "P6\n" << width << " " << height << "\n255\n";
	//ofs.write((char*)buffer, sizeof(unsigned char) * width * height * 3);
	//ofs.close(); */
	//delete [] buffer;

	for (unsigned i = 0; i < 1920 * 1080; ++i)
	{
		Vec3<float> vec;
		Matrix44X<float> mat;

		mat.multDirMatrix(Vec3<float>(), vec);
	}

	clock_t end1 = clock();

	clock_t start2 = clock();

	for (unsigned i = 0; i < 1920 * 1080; ++i)
	{
		Vector3 vec;
		Matrix44 mat;

		//mat.Multiply(Vector3(), vec);
	}

	clock_t end2 = clock();

	clock_t start3 = clock();

	for (unsigned i = 0; i < 1920 * 1080; ++i)
	{
		Vector3 vec;
		Matrix44 mat;

		vec = mat * Vector3();
	}

	clock_t end3 = clock();

	cout << "Time Elapsed: " << endl;
	cout << "Vec3 + Matrix44X: " << end1 - start1 << endl;
	cout << "Vector3 + Matrix44 + Multiply: " << end2 - start2 << endl;
	cout << "Vector3 + Matrix44 + *: " << end3 - start3 << endl;

	system("pause");

	return 0;
}
