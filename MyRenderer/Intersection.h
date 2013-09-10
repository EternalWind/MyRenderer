#pragma once

#include "IIntersectTarget.h"
#include "Ray.h"
#include "Vector3.h"

class IIntersectTarget;

struct ParycentricCoord
{
	float u;
	float v;
	float w;
};

class Intersection
{
public:
	Intersection(const Ray* test_object = nullptr, IIntersectTarget* intersect_object = nullptr, 
		float distance = numeric_limits<float>::max(), const ParycentricCoord& uvw = ParycentricCoord());

	const Ray* TestObject() const;

	IIntersectTarget* IntersectObject() const;

	float Distance() const;

	void SetTestObject(const Ray* test_object);

	void SetIntersectObject(IIntersectTarget* object);

	void SetDistance(float distance);

	ParycentricCoord ParycentricCoordinate() const;

	void SetParycentricCoordinate(const ParycentricCoord& coord);

	~Intersection(void);

private:
	const Ray* m_TestObjectHandle;
	IIntersectTarget* m_IntersectObjectHandle;
	float m_Distance;
	ParycentricCoord m_ParycentricCoord;
};

// Implementation for inline methods.
inline const Ray* Intersection::TestObject() const
{
	return m_TestObjectHandle;
}

inline IIntersectTarget* Intersection::IntersectObject() const 
{ 
	return m_IntersectObjectHandle; 
}

inline float Intersection::Distance() const
{
	return m_Distance;
}

inline void Intersection::SetTestObject(const Ray* test_object)
{
	m_TestObjectHandle = test_object;
}

inline void Intersection::SetIntersectObject(IIntersectTarget* object)
{
	m_IntersectObjectHandle = object;
}

inline void Intersection::SetDistance(float distance)
{
	m_Distance = distance;
}

inline ParycentricCoord Intersection::ParycentricCoordinate() const
{
	return m_ParycentricCoord;
}

inline void Intersection::SetParycentricCoordinate(const ParycentricCoord& coord)
{
	m_ParycentricCoord = coord;
}