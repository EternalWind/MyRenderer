#include "Scene.h"


Scene::Scene(const ColorRGBA& background_color) :
	m_BackgroundColor(background_color)
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

shared_ptr<IIntersectTarget> Scene::AddGeometry(shared_ptr<IIntersectTarget> geometry)
{
	m_Geometries.push_back(geometry);
	return geometry;
}

List(IIntersectTarget) Scene::Geometries() const
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

Scene::~Scene(void)
{
}
