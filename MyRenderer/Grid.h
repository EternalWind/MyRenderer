#pragma once

#include "Defs.h"
#include "Object.h"
#include "AABB.h"

class Grid
{
public:
	struct Cell
	{
		List(Triangle) triangles;
	};

	Grid(float resolution_parameter = 5.f, unsigned max_resolution = 128);

	void Initialize(const List(Object)& objects);

	shared_ptr<AABB> BoundingBox() const;

	const Cell& CellAt(unsigned x, unsigned y, unsigned z) const;

	const unsigned* Resolution() const;

	Vector3 CellSize() const;

	~Grid(void);

private:
	void Insert(shared_ptr<Object> object);

	Cell& _CellAt(unsigned x, unsigned y, unsigned z) const;

	shared_ptr<AABB> m_BoundingBox;
	vector<Cell> m_Cells;
	unsigned m_Resolution[3];
	Vector3 m_CellSize;
	float m_ResolutionParameter;
	unsigned m_MaxResolution;
};

// Implementation for inline methods.

inline shared_ptr<AABB> Grid::BoundingBox() const
{
	return m_BoundingBox;
}

inline const Grid::Cell& Grid::CellAt(unsigned x, unsigned y, unsigned z) const
{
	return _CellAt(x, y, z);
}

inline const unsigned* Grid::Resolution() const
{
	return m_Resolution;
}

inline Vector3 Grid::CellSize() const
{
	return m_CellSize;
}

inline Grid::Cell& Grid::_CellAt(unsigned x, unsigned y, unsigned z) const
{
#ifdef DEBUG
	if (x >= m_Resolution[0] || y >= m_Resolution[1] || z >= m_Resolution[2])
		throw Exception("Tried to access a cell which is not contained within the given grid.");
#endif
	return const_cast<Cell&>(m_Cells[x + y * m_Resolution[0] + z * m_Resolution[0] * m_Resolution[1]]);
}