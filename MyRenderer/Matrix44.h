#pragma once

#include "Vector3.h"
#include "Exception.h"

class Matrix44
{
public:
	/**
	  * Constructor. If no parameter is given, then it defaultly constructs an identity matrix.
	  */
	Matrix44(const float coefficients[4][4] = nullptr);

	float Coefficient(unsigned i, unsigned j) const;

	void SetCoefficient(unsigned i, unsigned j, float value);

	Matrix44 operator * (const Matrix44& right) const;

	Vector3 operator * (const Vector3& vec) const;

	Matrix44 Transpose() const;

	Matrix44 Inverse() const;

	~Matrix44(void);

private:
	float m_Coefficients[4][4];
};

