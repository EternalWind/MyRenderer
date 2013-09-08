#pragma once

#include <array>

#include "BezierCurve.h"

template <size_t rows, size_t columns>
class BezierSurface
{
public:
	BezierSurface(array < array<Vector3, columns>, rows > control_points = array < array<Vector3, columns>, rows >());

	Vector3 ControlPoint(unsigned row, unsigned column) const;

	void SetControlPoint(unsigned row, unsigned column, const Vector3& value);

	BezierCurve<columns> CurveAtRow(unsigned row) const;

	BezierCurve<rows> CurveAtColumn(unsigned column) const;

private:
	array < array<Vector3, columns>, rows > m_ControlPoints;
};

// Implementation for template methods.

template <size_t rows, size_t columns>
BezierSurface<rows, columns>::BezierSurface(array < array<Vector3, columns>, rows > control_points) :
	m_ControlPoints(control_points) {}

template <size_t rows, size_t columns>
Vector3 BezierSurface<rows, columns>::ControlPoint(unsigned row, unsigned column) const
{
	return m_ControlPoints[row][column];
}

template <size_t rows, size_t columns>
void BezierSurface<rows, columns>::SetControlPoint(unsigned row, unsigned column, const Vector3& value)
{
	m_ControlPoints[row][column] = value;
}

template <size_t rows, size_t columns>
BezierCurve<columns> BezierSurface<rows, columns>::CurveAtRow(unsigned row) const
{
	return BezierCurve<columns>(m_ControlPoints[row]);
}

template <size_t rows, size_t columns>
BezierCurve<rows> BezierSurface<rows, columns>::CurveAtColumn(unsigned column) const
{
	array<Vector3, rows> data;

	for (unsigned i = 0; i < rows; ++i)
		data[i] = m_ControlPoints[i][column];

	return BezierCurve<rows>(data);
}