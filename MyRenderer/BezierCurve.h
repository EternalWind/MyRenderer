#pragma once

#include <array>

#include "Vector3.h"

template <size_t n>
class BezierCurve
{
public:
	BezierCurve(array<Vector3, n> control_points = array<Vector3, n>());

	Vector3 ControlPoint(unsigned i) const;

	void SetControlPoint(unsigned i, const Vector3& value);

	Vector3 PointAt(float t);

	Vector3 PointAtDCA(float t, const Vector3* cps = nullptr, unsigned length = n);

	pair<BezierCurve<n>, BezierCurve<n>> SplitAt(float t);

private:
	unsigned Factorial(unsigned n) const;

	array<Vector3, n> m_ControlPoints;
	array<unsigned, n> m_Factorials;
};

typedef BezierCurve<4> BezierCurveCubic;

// Implementation for template methods.

template <size_t n>
BezierCurve<n>::BezierCurve(array<Vector3, n> control_points) :
	m_ControlPoints(control_points) 
{
	for (unsigned i = 0; i < n; ++i)
	{
		m_Factorials[i] = Factorial(i);
	}
}

template <size_t n>
Vector3 BezierCurve<n>::ControlPoint(unsigned i) const
{
	return m_ControlPoints[i];
}

template <size_t n>
void BezierCurve<n>::SetControlPoint(unsigned i, const Vector3& value)
{
	m_ControlPoints[i] = value;
}

template <size_t n>
Vector3 BezierCurve<n>::PointAt(float t)
{
	Vector3 result;

	for (unsigned i = 0; i < n; ++i)
	{
		float k = float(pow(t, i) * pow(1.f - t, n - i - 1) * m_Factorials[n - 1] / (m_Factorials[i] * m_Factorials[n - i - 1]));
		result = result + m_ControlPoints[i] * k;
	}

	return result;
}

template <size_t n>
pair<BezierCurve<n>, BezierCurve<n>> BezierCurve<n>::SplitAt(float t)
{
	array<Vector3, n> cps1;
	array<Vector3, n> cps2;
	
	unsigned length = n;
	unsigned i = 0;

	Vector3* temp = new Vector3[n];

	memcpy(temp, m_ControlPoints.data(), sizeof(Vector3) * n);

	while (length > 0)
	{
		cps1[i] = temp[0];
		cps2[n - i - 1] = temp[length - 1];

		for (unsigned j = 0; j < length - 1; ++j)
		{
			length[j] = length[j] * (1 - t) + length[j + 1] * t;
		}

		++i;
		--length;
	}

	return pair<BezierCurve<n>, BezierCurve<n>>(BezierCurve<n>(cps1), BezierCurve<n>(cps2));
}

template <size_t n>
Vector3 BezierCurve<n>::PointAtDCA(float t, const Vector3* cps, unsigned length)
{
	if (cps == nullptr)
		cps = m_ControlPoints.data();

	if (length == 1)
		return *cps;

	Vector3* new_cps = new Vector3[length - 1];

	for (unsigned i = 0; i < length - 1; ++i)
	{
		new_cps[i] = cps[i] * (1 - t) + cps[i + 1] * t;
	}

	return PointAtDCA(t, new_cps, length - 1);
}

template <size_t n>
unsigned BezierCurve<n>::Factorial(unsigned x) const
{
	return x == 0 || x == 1 ? 1 : x * Factorial(x - 1);
}