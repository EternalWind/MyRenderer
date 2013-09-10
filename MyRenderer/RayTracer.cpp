#include "RayTracer.h"

#include <time.h>

RayTracer::RayTracer(void)
{
}

void RayTracer::Render() const
{
	for (auto iter_s = m_Scenes.begin(); iter_s != m_Scenes.end(); ++iter_s)
	{
		auto scene = *iter_s;
		auto cameras = scene->Cameras();
		auto geometries = scene->Geometries();
		ColorRGBA background_color = scene->BackgroundColor();

		for (auto iter_c = cameras.begin(); iter_c != cameras.end(); ++iter_c)
		{
			auto camera = *iter_c;
			auto render_target = camera->RenderTarget();

			unsigned width = render_target->Width();
			unsigned height = render_target->Height();

			float aspect_ratio = width >= height ? (float)width / height : (float)height / width;
			float tan_fov = tan(camera->FOV() / 2);
			float near = camera->NearClippingPlane();
			float far = camera->FarClippingPlane();

			const Matrix44& c2w = camera->CameraToWorld();

			Vector3 cam_pos = camera->Position();

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
					pixel_center = c2w * pixel_center;

					Vector3 ray_direction(pixel_center - cam_pos);
					ray_direction.Normalise();

					Ray ray(cam_pos, ray_direction, Range<float>(near, far));

					render_target->SetPixel(i, j, Trace(ray, geometries, background_color));
				}
		}
	}
}

ColorRGBA RayTracer::Trace(const Ray& ray, const List(IIntersectTarget)& geometries, const ColorRGBA& background_color) const
{
	Intersection closest_hit;
	float cloest_distance = ray.EffectRange().Max;

	for (auto iter_g = geometries.begin(); iter_g != geometries.end(); ++iter_g)
	{
		auto geometry = *iter_g;
		Intersection hit;

		if (geometry->Intersect(ray, hit) && hit.Distance() < cloest_distance)
		{
			closest_hit = hit;
			cloest_distance = hit.Distance();
		}
	}

	if (m_IsWireFrame)
	{
		if (cloest_distance < ray.EffectRange().Max)
		{
			ParycentricCoord uvw = closest_hit.ParycentricCoordinate();
			float epsilon = 0.01f;

			if (uvw.u < epsilon || uvw.v < epsilon || uvw.w < epsilon)
				return ColorRGBA(1.f, 1.f, 1.f);
		}

		return background_color;
	}
	else
	{
		if (cloest_distance < ray.EffectRange().Max)
			return Shade(ray, closest_hit);
		else
			return background_color;
	}
}

ColorRGBA RayTracer::Shade(const Ray& ray, const Intersection& intersection) const
{
	auto uvw = intersection.ParycentricCoordinate();

	return ColorRGBA(uvw.u, uvw.v, uvw.w);
}

RayTracer::~RayTracer(void)
{
}
