#pragma once

#include <array>

#include "Vector3.h"

template <size_t n>
class Bezier
{
public:
	Bezier(array<Vector3, n> control_points);

	Vector3 PointAt(float t);

	pair<Bezier<4>, Bezier<4>> SplitAt(float t);

private:
	array<Vector3, n> m_ControlPoints;
	array<unsigned, n> m_Factorials;
};

// Implementation for template methods.

template <size_t n>
Bezier<n>::Bezier(array<Vector3, n> control_points) :
	m_ControlPoints(control_points) 
{
	for (unsigned i = 0; i < n; ++i)
	{
		m_Factorials[i] = Factorial(i);
	}
}

template <size_t n>
Vector3 Bezier<n>::PointAt(float t)
{
	Vector3 result;

	for (unsigned i = 0; i < n; ++i)
	{
		float k = pow(t, i) * pow(1.f - t, n - i - 1) * m_Factorials[n - 1] / (m_Factorials[i] * m_Factorials[n - i - 1]);
		result = result + m_ControlPoints[i] * k;
	}

	return result;
}

template <size_t n>
pair<Bezier<4>, Bezier<4>> Bezier<n>::SplitAt(float t)
{
	if (n != 4)
		throw Exception("SplitAt() is only supported by Bezier<4>.");

	array<Vector3, 4> cps1;
	array<Vector3, 4> cps2;
	
	Vector3 p01 = m_ControlPoints[0] * (1 - t) + m_ControlPoints[1] * t;
	Vector3 p12 = m_ControlPoints[1] * (1 - t) + m_ControlPoints[2] * t;
	Vector3 p23 = m_ControlPoints[2] * (1 - t) + m_ControlPoints[3] * t;

	Vector3 p0112 = p01 * (1 - t) + p12 * t;
	Vector3 p1223 = p12 * (1 - t) + p23 * t;

	cps1[0] = m_ControlPoints[0];
	cps1[1] = p01;
	cps1[2] = p0112;
	cps1[3] = cps2[0] = p0112 * (1 - t) + p1223 * t;
	cps2[1] = p1223;
	cps2[2] = p23;
	cps2[3] = m_ControlPoints[3];

	return pair<Bezier<4>, Bezier<4>>(Bezier<4>(cps1), Bezier<4>(cps2));
}