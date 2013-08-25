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

void Camera::Render()
{
	unsigned width = m_RenderTarget->Width();
	unsigned height = m_RenderTarget->Height();
	float aspect_ratio = width >= height ? (float)width / height : (float)height / width;
	float tan_fov = tan(m_FOV / 2);

	for (unsigned i = 0; i < height; ++i)
		for (unsigned j = 0; j < width; ++j)
		{
			float px = ((j + .5f) / width * 2 - 1) * tan_fov;
			float py = (1 - (i + .5f) / height * 2) * tan_fov;;

			if (width >= height)
			{
				px *= aspect_ratio;
			}
			else
			{
				py *= aspect_ratio;
			}

			Vector3 pixel_center(px, py, -1);
			pixel_center = m_C2WTransformation * pixel_center;

			Vector3 ray_direction(pixel_center - m_Position);
			ray_direction.Normalise();

			// TODO: Replace the following code with real rendering code.
			m_RenderTarget->SetPixel(i, j, ColorRGBA((1 + ray_direction.X()) * .5f, (1 + ray_direction.Y()) * .5f));
		}
}

Camera::~Camera(void)
{
}
