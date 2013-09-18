#pragma once

#include "IIntersectTarget.h"

class Object :
	public IIntersectTarget
{
public:
	Object(void);

	void Initialize();

	bool Intersect(const Ray& ray, Intersection& intersection, void* additional_data = nullptr) const;

	bool IsDoubleSided() const;

	void EnableDoubleSided(bool is_double_sided);

	virtual ~Object(void);

protected:
	virtual shared_ptr<IIntersectTarget> ConstructBoundingVolume() const = 0;

	virtual void OnEnableDoubleSided(bool is_double_sided) = 0;

	virtual bool OnIntersect(const Ray& ray, Intersection& intersection, void* additional_data) const = 0;

private:
	bool m_IsInitialized;
	bool m_IsDoubleSided;
	shared_ptr<IIntersectTarget> m_BoundingVolume;
};

