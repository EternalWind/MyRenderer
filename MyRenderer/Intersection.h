#pragma once

#include "IIntersectTarget.h"
#include "Vector3.h"

class IIntersectTarget;

class Intersection
{
public:
	Intersection(const Vector3& position, const IIntersectTarget* object, float distance);

	Vector3 Position() const;

	IIntersectTarget* IntersectObject() const;

	float Distance() const;

	void SetPosition(const Vector3& position);

	void SetIntersectObject(IIntersectTarget* object);

	void SetDistance(float distance);

	~Intersection(void);

private:
	Vector3 m_Position;
	IIntersectTarget* m_IntersectObjectHandle;
	float m_Distance;
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

inline float Intersection::Distance() const
{
	return m_Distance;
}

inline void Intersection::SetPosition(const Vector3& position)
{
	m_Position = position;
}

inline void Intersection::SetIntersectObject(IIntersectTarget* object)
{
	m_IntersectObjectHandle = object;
}

inline void Intersection::SetDistance(float distance)
{
	m_Distance = distance;
}