#pragma once

#include "IIntersectTarget.h"
#include "Vector3.h"

class IIntersectTarget;

class Intersection
{
public:
	Intersection(const Vector3& position, const IIntersectTarget* object);

	Vector3 Position() const;

	IIntersectTarget* IntersectObject() const;

	~Intersection(void);

private:
	Vector3 m_Position;
	IIntersectTarget* m_IntersectObjectHandle;
};

// Implementation for inline methods.
inline Vector3 Intersection::Position() const
{
	return m_Position;
}

inline IIntersectTarget* Intersection::IntersectObject() const 
{ 
	return m_IntersectObjectHandle; 
}