#pragma once

#include <memory>

#include "Vector3.h"
#include "Matrix44.h"
#include "IRenderTarget.h"

using namespace std;

class Camera
{
public:
	Camera(shared_ptr<IRenderTarget> target, const Vector3& position = Vector3());

	/**
	  * Transform the camera. Please do not pass a Matrix44 contains scaling for now.
	  */
	void Transform(const Matrix44& transformation);

	Vector3 Position() const;

	Vector3 Orientation() const;

	Vector3 Up() const;

	shared_ptr<IRenderTarget> RenderTarget() const;

	float FOV() const;

	void SetRenderTarget(shared_ptr<IRenderTarget> target);

	void SetFOV(float fov);

	void Render();

	float NearClippingPlane() const;

	float FarClippingPlane() const;

	void SetNearClippingPlane(float near_clipping_plane);

	void SetFarClippingPlane(float far_clipping_plane);

	const Matrix44& CameraToWorld() const;

	const Matrix44& WorldToCamera() const;

	~Camera(void);

protected:
	Vector3 m_Position;
	Vector3 m_Orientation;
	Vector3 m_Up;
	Matrix44 m_C2WTransformation;
	Matrix44 m_W2CTransformation;
	shared_ptr<IRenderTarget> m_RenderTarget;
	float m_FOV;                                      //!< The vertical field of view angle.
	float m_NearClippingPlane;
	float m_FarClippingPlane;
};


// Inline method implementatons.

inline Vector3 Camera::Position() const
{
	return m_Position;
}

inline Vector3 Camera::Orientation() const
{
	return m_Orientation;
}

inline Vector3 Camera::Up() const
{
	return m_Up;
}

inline shared_ptr<IRenderTarget> Camera::RenderTarget() const
{
	return m_RenderTarget;
}

inline float Camera::FOV() const
{
	return m_FOV;
}

inline void Camera::SetRenderTarget(shared_ptr<IRenderTarget> target)
{
	m_RenderTarget = target;
}

inline void Camera::SetFOV(float fov)
{
	m_FOV = fov;
}

inline float Camera::NearClippingPlane() const
{
	return m_NearClippingPlane;
}

inline float Camera::FarClippingPlane() const
{
	return m_FarClippingPlane;
}

inline void Camera::SetNearClippingPlane(float near_clipping_plane)
{
	m_NearClippingPlane = near_clipping_plane;
}

inline void Camera::SetFarClippingPlane(float far_clipping_plane)
{
	m_FarClippingPlane = far_clipping_plane;
}

inline const Matrix44& Camera::CameraToWorld() const
{
	return m_C2WTransformation;
}

inline const Matrix44& Camera::WorldToCamera() const
{
	return m_W2CTransformation;
}