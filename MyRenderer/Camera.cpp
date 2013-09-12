#include <math.h>

#include "Camera.h"


Camera::Camera(shared_ptr<IRenderTarget> target, const Vector3& position) :
	m_Position(position),
	m_Orientation(0.f, 0.f, -1.f),
	m_Up(0.f, 1.f, 0.f),
	m_RenderTarget(target),
	m_FOV((float)M_PI_2)
{
	m_C2WTransformation.SetCoefficient(0, 3, position.X());
	m_C2WTransformation.SetCoefficient(1, 3, position.Y());
	m_C2WTransformation.SetCoefficient(2, 3, position.Z());

	m_W2CTransformation.SetCoefficient(0, 3, -position.X());
	m_W2CTransformation.SetCoefficient(1, 3, -position.Y());
	m_W2CTransformation.SetCoefficient(2, 3, -position.Z());
}

void Camera::Transform(const Matrix44& transformation)
{
	m_Position = transformation * m_Position;
	m_Orientation = transformation * m_Orientation;
	m_Up = transformation * m_Up;
	m_C2WTransformation = transformation * m_C2WTransformation;
	m_W2CTransformation = m_C2WTransformation.Inverse();
}

Camera::~Camera(void)
{
}
