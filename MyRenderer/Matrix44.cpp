#include "Matrix44.h"

Matrix44::Matrix44(const float coefficients[4][4])
{
	size_t buffer_size = sizeof(float) * 16;

	if (coefficients != nullptr)
	{
		memcpy_s(m_Coefficients, buffer_size, coefficients, buffer_size);
	}
	else
	{
		float identity[4][4] = { 1.0f, 0.0f, 0.0f, 0.0f,
			                     0.0f, 1.0f, 0.0f, 0.0f,
								 0.0f, 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 0.0f, 1.0f };

		memcpy_s(m_Coefficients, buffer_size, identity, buffer_size);
	}
}

float Matrix44::Coefficient(unsigned i, unsigned j) const
{
	if (i > 3 || j > 3)
		throw Exception("The given index is out of scope!");

	return m_Coefficients[i][j];
}

void Matrix44::SetCoefficient(unsigned i, unsigned j, float value)
{
	if (i > 3 || j > 3)
		throw Exception("The given index is out of scope!");

	m_Coefficients[i][j] = value;
}

Matrix44 Matrix44::operator * (const Matrix44& right) const
{
	const Matrix44& left = *this;
	Matrix44 product;

	for (unsigned i = 0; i < 4; ++i)
		for (unsigned j = 0; j < 4; ++j)
			for (unsigned k = 0; k < 4; ++k)
				product.m_Coefficients[i][j] += left.m_Coefficients[i][k] * right.m_Coefficients[k][j];

	return product;
}

Vector3 Matrix44::operator * (const Vector3& vec) const
{
	Vector3 product;

	product.SetX(vec.X() * m_Coefficients[0][0] + vec.Y() * m_Coefficients[0][1] + vec.Z() * m_Coefficients[0][2] + m_Coefficients[0][3]);
	product.SetY(vec.X() * m_Coefficients[1][0] + vec.Y() * m_Coefficients[1][1] + vec.Z() * m_Coefficients[1][2] + m_Coefficients[1][3]);
	product.SetZ(vec.X() * m_Coefficients[2][0] + vec.Y() * m_Coefficients[2][1] + vec.Z() * m_Coefficients[2][2] + m_Coefficients[2][3]);

	if (m_Coefficients[3][0] != 0.0f || m_Coefficients[3][1] != 0.0f || m_Coefficients[3][2] != 0.0f || m_Coefficients[3][3] != 1.0f)
	{
		float w = vec.X() * m_Coefficients[3][0] + vec.Y() * m_Coefficients[3][1] + vec.Z() * m_Coefficients[3][2] + m_Coefficients[3][3];

		product.SetX(product.X() / w);
		product.SetY(product.Y() / w);
		product.SetZ(product.Z() / w);
	}

	return product;
}

Matrix44 Matrix44::Transpose() const
{
	Matrix44 result;

	for (unsigned i = 0; i < 4; ++i)
		for (unsigned j = 0; j < 4; ++j)
			result.m_Coefficients[i][j] = m_Coefficients[j][i];

	return result;
}

Matrix44 Matrix44::Inverse() const
{
	Matrix44 result;
	float cofactors[16], det, *m = (float*)m_Coefficients;

    cofactors[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    cofactors[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    cofactors[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    cofactors[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    cofactors[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    cofactors[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    cofactors[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    cofactors[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    cofactors[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    cofactors[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    cofactors[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    cofactors[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    cofactors[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    cofactors[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    cofactors[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    cofactors[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * cofactors[0] + m[1] * cofactors[4] + m[2] * cofactors[8] + m[3] * cofactors[12];

    if (det == 0.0f)
        return result;

    det = 1.0f / det;

	float* res_data = (float*)result.m_Coefficients;

	for (unsigned i = 0; i < 16; ++i)
			res_data[i] = cofactors[i] * det;

	return result;
}

Matrix44::~Matrix44(void)
{
}
