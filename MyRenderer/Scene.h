#pragma once

#include "IScene.h"

class Scene : public IScene
{
public:
	Scene(const ColorRGBA& background_color);

	shared_ptr<Camera> AddCamera(shared_ptr<Camera> camera);

	List(Camera) Cameras() const;

	shared_ptr<Object> AddGeometry(shared_ptr<Object> geometry);

	List(Object) Geometries() const;

	ColorRGBA BackgroundColor() const;

	void SetBackgroundColor(const ColorRGBA& background_color);

	void Initialize();

    virtual ~Scene(void);

protected:
	virtual void OnInitialize() = 0;

	List(Camera) m_Cameras;
	List(Object) m_Geometries;
	ColorRGBA m_BackgroundColor;
	bool m_IsInitialized;
};

