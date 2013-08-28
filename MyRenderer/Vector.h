#pragma once

#include <math.h>

#include "Exception.h"

/**
* A column-order vector.
*/
template <size_t size>
class Vector
{
public:
	Vector(void) {}

	virtual ~Vector(void) {}

	float ElementAt(unsigned index) const;

	void SetElementAt(unsigned index, float value);

	float SquareLength() const;

	float Length() const;

	Vector<size> operator * (float value) const;

	Vector<size> operator + (const Vector<size>& other) const;

	Vector<size> operator - () const;

	Vector<size> operator - (const Vector<size>& other) const;

	Vector<size> operator / (float value) const;

	Vector<size> operator == (const Vector<size>& other) const;

	Vector<size> operator != (const Vector<size>& other) const;

	float Normalise();

	float DotProduct(const Vector<size>& other) const;

	bool IsZeroLength() const;

protected:
	float m_Elements[size];
};

// Implementation for template class.

template <size_t size>
float inline Vector<size>::ElementAt(unsigned index) const
{
	if (index < size)
	{
		return m_Elements[index];
	}
	else
	{
		throw Exception("The given index is out of the scope!");
	}
}

template <size_t size>

void inline Vector<size>::SetElementAt(unsigned index, float value)
{
	if (index < size)
	{
		m_Elements[index] = value;
	}
	else
	{
		throw Exception("The given index is out of the scope!");
	}
}

template <size_t size>
float Vector<size>::SquareLength() const
{
	return this->DotProduct(*this);
}

template <size_t size>
float Vector<size>::Length() const
{
	return sqrt(SquareLength());
}

template <size_t size>
Vector<size> inline Vector<size>::operator * (float value) const
{
	Vector<size> result;

	for (unsigned i = 0; i < size; ++i)
	{
		result.m_Elements[i] = this->m_Elements[i] * value;
	}

	return result;
}

template <size_t size>
Vector<size> inline Vector<size>::operator + (const Vector<size>& other) const
{
	Vector<size> result;

	for (unsigned i = 0; i < size; ++i)
	{
		result.m_Elements[i] = this->m_Elements[i] + other.m_Elements[i];
	}

	return result;
}

template <size_t size>
Vector<size> inline Vector<size>::operator - () const
{
	return *this * -1;
}

template <size_t size>
Vector<size> inline Vector<size>::operator - (const Vector<size>& other) const
{
	return *this + (-other);
}

template <size_t size>
Vector<size> inline Vector<size>::operator / (float value) const
{
	return *this * (1 / value);
}

template <size_t size>
Vector<size> inline Vector<size>::operator == (const Vector<size>& other) const
{
	for (unsigned i = 0; i < size; ++i)
	{
		if (this->m_Elements[i] != other.m_Elements[i])
		{
			return false;
		}
	}

	return true;
}

template <size_t size>
Vector<size> inline Vector<size>::operator != (const Vector<size>& other) const
{
	return !(*this == other);
}

template <size_t size>
float Vector<size>::Normalise()
{
	float length = this->Length();

	if (length != 0)
	{
		*this = *this / length;
	}
	else
	{
		throw Exception("Try to normalise a zero-length vector!");
	}

	return length;
}

template <size_t size>
float Vector<size>::DotProduct(const Vector<size>& other) const
{
	float result = 0.0f;

	for (unsigned i = 0; i < size; ++i)
	{
		result += this->m_Elements[i] * other.m_Elements[i];
	}

	return result;
}

template <size_t size>
bool Vector<size>::IsZeroLength() const
{
	for (unsigned i = 0; i < size; ++i)
	{
		if (m_Elements[i] != 0.f)
			return false;
	}

	return true;
}