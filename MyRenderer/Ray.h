#pragma once

#include <math.h>

#include "Vector3.h"
#include "Math.h"

class Ray
{
public:
	Ray(const Vector3& origin, const Vector3& direction, const Range<float>& effect_range = Range<float>(0.f, std::numeric_limits<float>::max()));

	Vector3 Origin() const;

	Vector3 Direction() const;

	Vector3 InvDirection() const;

	Range<float> EffectRange() const;

	void SetEffectRange(const Range<float>& effect_range);

	~Ray(void);

private:
	Vector3 m_Origin;
	Vector3 m_Direction;
	Vector3 m_InvDirection;
	Range<float> m_EffectRange;
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

inline Range<float> Ray::EffectRange() const
{
	return m_EffectRange;
}

inline void Ray::SetEffectRange(const Range<float>& effect_range)
{
	m_EffectRange = effect_range;
}