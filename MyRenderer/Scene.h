#pragma once

#include <memory>
#include <vector>

#include "Camera.h"
#include "IIntersectTarget.h"

using namespace std;

#define List(T) vector<shared_ptr<T>>

class Scene
{
public:
	Scene(const ColorRGBA& background_color = ColorRGBA());

	shared_ptr<Camera> AddCamera(shared_ptr<Camera> camera);

	List(Camera) Cameras() const;

	shared_ptr<IIntersectTarget> AddGeometry(shared_ptr<IIntersectTarget> geometry);

	List(IIntersectTarget) Geometries() const;

	ColorRGBA BackgroundColor() const;

	void SetBackgroundColor(const ColorRGBA& background_color);

    ~Scene(void);

private:
	List(Camera) m_Cameras;
	List(IIntersectTarget) m_Geometries;
	ColorRGBA m_BackgroundColor;
};

