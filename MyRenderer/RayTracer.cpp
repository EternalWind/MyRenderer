#include "RayTracer.h"
#include "Profiler.h"
#include "Volume.h"

#include <time.h>

RayTracer::RayTracer(void)
{
}

void RayTracer::Render() const
{
	clock_t start, end;
	start = clock();

	Profiler::numPrimaryRaysPerFrame = 0;
	Profiler::numIntersectionPerFrame = 0;
	Profiler::numRayTriangleTestsPerFrame = 0;
	Profiler::numRayVolumeTestsPerFrame = 0;

	for (auto iter_s = m_Scenes.begin(); iter_s != m_Scenes.end(); ++iter_s)
	{
		auto scene = *iter_s;
		auto cameras = scene->Cameras();

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
					++Profiler::numPrimaryRaysPerFrame;

					render_target->SetPixel(i, j, Trace(ray, scene));
				}
		}
	}

	end = clock();

	Profiler::renderTimePerFrame = float(end - start) / CLOCKS_PER_SEC;
}

ColorRGBA RayTracer::Trace(const Ray& ray, shared_ptr<IScene> scene) const
{
	Intersection intersection;

	if (scene->Intersect(ray, intersection) && intersection.Distance() < ray.EffectRange().Max)
	{
		if (m_IsWireFrame)
		{
			ParycentricCoord uvw = intersection.ParycentricCoordinate();
			float epsilon = 0.01f;

			if (uvw.u < epsilon || uvw.v < epsilon || uvw.w < epsilon)
				return ColorRGBA(1.f, 1.f, 1.f);
		}
		else
		{
			return Shade(ray, intersection);
		}
	}

	return scene->BackgroundColor();
}

ColorRGBA RayTracer::Shade(const Ray& ray, const Intersection& intersection) const
{
	auto uvw = intersection.ParycentricCoordinate();

	return ColorRGBA(uvw.u, uvw.v, uvw.w);
}

RayTracer::~RayTracer(void)
{
}
