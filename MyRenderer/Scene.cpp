#include "Scene.h"


Scene::Scene(const ColorRGBA& background_color) :
	m_BackgroundColor(background_color),
	m_IsInitialized(false)
{
}

shared_ptr<Camera> Scene::AddCamera(shared_ptr<Camera> camera)
{
	m_Cameras.push_back(camera);
	return camera;
}

List(Camera) Scene::Cameras() const
{
	return m_Cameras;
}

shared_ptr<Object> Scene::AddGeometry(shared_ptr<Object> geometry)
{
	geometry->Initialize();
	m_Geometries.push_back(geometry);

	return geometry;
}

List(Object) Scene::Geometries() const
{
	return m_Geometries;
}

ColorRGBA Scene::BackgroundColor() const
{
	return m_BackgroundColor;
}

void Scene::SetBackgroundColor(const ColorRGBA& background_color)
{
	m_BackgroundColor = background_color;
}

void Scene::Initialize()
{
	if (!m_IsInitialized)
	{
		OnInitialize();
		m_IsInitialized = true;
	}
}

Scene::~Scene(void)
{
}
