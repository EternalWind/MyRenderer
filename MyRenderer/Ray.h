#pragma once

#include <math.h>

#include "Vector3.h"

class Ray
{
public:
	Ray(const Vector3& origin, const Vector3& direction, float max_length = std::numeric_limits<float>::max(), float min_length = 0.f);

	Vector3 Origin() const;

	Vector3 Direction() const;

	Vector3 InvDirection() const;

	float MaxLength() const;

	float MinLength() const;

	~Ray(void);

private:
	Vector3 m_Origin;
	Vector3 m_Direction;
	Vector3 m_InvDirection;
	float m_MaxLength;
	float m_MinLength;
};

inline Vector3 Ray::Origin() const
{
	return m_Origin;
}

inline Vector3 Ray::Direction() const
{
	return m_Direction;
}

inline Vector3 Ray::InvDirection() const
{
	return m_InvDirection;
}

inline float Ray::MaxLength() const
{
	return m_MaxLength;
}

inline float Ray::MinLength() const
{
	return m_MinLength;
}