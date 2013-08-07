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

	float inline ElementAt(unsigned index) const
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

	void inline SetElementAt(unsigned index, float value)
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

	float SquareLength() const
	{
		return this->DotProduct(*this);
	}

	float Length() const
	{
		return sqrt(SquareLength());
	}

	Vector<size> inline operator * (float value) const
	{
		Vector<size> result;

		for (unsigned i = 0; i < size; ++i)
		{
			result.m_Elements[i] = this->m_Elements[i] * value;
		}

		return result;
	}

	Vector<size> inline operator + (const Vector<size>& other) const
	{
		Vector<size> result;

		for (unsigned i = 0; i < size; ++i)
		{
			result.m_Elements[i] = this->m_Elements[i] + other.m_Elements[i];
		}

		return result;
	}

	Vector<size> inline operator - () const
	{
		return *this * -1;
	}

	Vector<size> inline operator - (const Vector<size>& other) const
	{
		return *this + (-other);
	}

	Vector<size> inline operator / (float value) const
	{
		return *this * (1 / value);
	}

	Vector<size> inline operator == (const Vector<size>& other) const
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

	Vector<size> inline operator != (const Vector<size>& other) const
	{
		return !(*this == other);
	}

	float Normalise()
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

	float DotProduct(const Vector<size>& other) const
	{
		float result = 0.0f;

		for (unsigned i = 0; i < size; ++i)
		{
			result += this->m_Elements[i] * other.m_Elements[i];
		}

		return result;
	}

protected:
	float m_Elements[size];
};

