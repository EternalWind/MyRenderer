#pragma once

#include "IIntersectTarget.h"

class Object :
	public IIntersectTarget
{
public:
	Object(void);

	bool Intersect(const Ray& ray, Intersection& intersection) const;

	bool IsDoubleSided() const;

	void EnableDoubleSided(bool is_double_sided);

	virtual ~Object(void);

protected:
	virtual void OnEnableDoubleSided(bool is_double_sided) = 0;

	virtual bool OnIntersect(const Ray& ray, Intersection& intersection) const = 0;

	bool m_IsDoubleSided;
	shared_ptr<IIntersectTarget> m_BoundingVolume;
};

