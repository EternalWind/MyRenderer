#pragma once
#include "Exception.h"

template <class T>
struct Range
{
	Range(const T& min = 0.f, const T& max = 0.f) :
		Min(min), Max(max) 
	{
		if (Max < Min)
			throw Exception("A minimal value greater than the maximal value is given.");
	}

	T Min;
	T Max;
};

class Math
{
public:
	template <class T>
	static T Clamp(const T& value, const T& max, const T& min);

	template <class T>
	static int Sign(const T& value);

	/**
	  * Solve a given quadratic equation. The returned x0 is always smaller than or equals to x1.
	  */
	template <class T>
	static bool SolveQuadratic(const T& a, const T& b, const T& c, T& x0, T& x1);

	template <class T>
	static bool Overlap(const Range<T>& range1, const Range<T>& range2);

private:
	Math(void);

	Math(const Math& other);

	Math operator = (const Math& other);
};

// Implementation for template methods.

template <class T>
inline T Math::Clamp(const T& value, const T& max, const T& min)
{
	if (max < min)
		throw Exception("The given maximun value cannot be smaller than the given minimun value.");

	T clamped_value = value;

	if (clamped_value > max)
		return max;
	else if (clamped_value < min)
		return min;
	else
		return clamped_value;
}

template <class T>
inline int Math::Sign(const T& value)
{
	return value >= 0 ? 1 : -1;
}

template <class T>
inline bool Math::SolveQuadratic(const T& a, const T& b, const T& c, T& x0, T& x1)
{
	T discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return false;

	T q = T(-0.5) * (b + Sign(b) * (T)std::sqrt(discriminant));
	x1 = q / a;

	if (discriminant == 0)
	{
		x0 = x1;
		return true;
	}
	else
	{
		x0 = c / q;

		if (x0 > x1)
			std::swap(x0, x1);

		return true;
	}
}

template <class T>
inline bool Math::Overlap(const Range<T>& range1, const Range<T>& range2)
{
	return !(range1.Min > range2.Max || range1.Max < range2.Min);
}