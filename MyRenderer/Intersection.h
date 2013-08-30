#pragma once

#include "IIntersectTarget.h"
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
	Intersection(const Vector3& position, const IIntersectTarget* object, float distance, const ParycentricCoord& uvw = ParycentricCoord());

	Vector3 Position() const;

	IIntersectTarget* IntersectObject() const;

	float Distance() const;

	void SetPosition(const Vector3& position);

	void SetIntersectObject(IIntersectTarget* object);

	void SetDistance(float distance);

	ParycentricCoord ParycentricCoordinate() const;

	void SetParycentricCoordinate(const ParycentricCoord& coord);

	~Intersection(void);

private:
	Vector3 m_Position;
	IIntersectTarget* m_IntersectObjectHandle;
	float m_Distance;
	ParycentricCoord m_ParycentricCoord;
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

inline ParycentricCoord Intersection::ParycentricCoordinate() const
{
	return m_ParycentricCoord;
}

inline void Intersection::SetParycentricCoordinate(const ParycentricCoord& coord)
{
	m_ParycentricCoord = coord;
}