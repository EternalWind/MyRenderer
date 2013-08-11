#pragma once
#include "Exception.h"

class Math
{
public:
	template <class T>
	static inline T Clamp(T value, T max, T min);

private:
	Math(void);

	Math(const Math& other);

	Math operator = (const Math& other);
};

// Implementation for template methods.

template <class T>
T Math::Clamp(T value, T max, T min)
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