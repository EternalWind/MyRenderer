#pragma once

#include "Camera.h"
#include "Object.h"
#include "ColorRGBA.h"
#include "IIntersectTarget.h"

class IScene : public IIntersectTarget
{
public:
	virtual shared_ptr<Camera> AddCamera(shared_ptr<Camera> camera) = 0;

	virtual List(Camera) Cameras() const = 0;

	virtual shared_ptr<Object> AddGeometry(shared_ptr<Object> geometry) = 0;

	virtual List(Object) Geometries() const = 0;

	virtual ColorRGBA BackgroundColor() const = 0;

	virtual void SetBackgroundColor(const ColorRGBA& background_color) = 0;

	virtual void Initialize() = 0;

	virtual ~IScene() = 0 {}
};