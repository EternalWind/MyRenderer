#pragma once

#include <array>

#include "BezierCurve.h"

template <size_t rows, size_t columns>
class BezierSurface
{
public:
	BezierSurface(Vector3 control_points[rows][columns] = nullptr);

	Vector3 ControlPoint(unsigned row, unsigned column) const;

	void SetControlPoint(unsigned row, unsigned column, const Vector3& value);

	BezierCurve<columns> CurveAtRow(unsigned row) const;

	BezierCurve<rows> CurveAtColumn(unsigned column) const;

private:
	Vector3 m_ControlPoints[rows][columns];
};

// Implementation for template methods.

template <size_t rows, size_t columns>
BezierSurface<rows, columns>::BezierSurface(Vector3 control_points[rows][columns]) 
{
	if (control_points != nullptr)
		memcpy_s(m_ControlPoints, sizeof(Vector3) * rows * columns, control_points, sizeof(Vector3) * rows * columns);
}

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
	Vector3 data[columns];
	
	for (unsigned i = 0; i < columns; ++i)
		data[i] = m_ControlPoints[row][i];

	return BezierCurve<columns>(data);
}

template <size_t rows, size_t columns>
BezierCurve<rows> BezierSurface<rows, columns>::CurveAtColumn(unsigned column) const
{
	Vector3 data[rows];

	for (unsigned i = 0; i < rows; ++i)
		data[i] = m_ControlPoints[i][column];

	return BezierCurve<rows>(data);
}