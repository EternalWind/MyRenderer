#include "Renderer.h"


Renderer::Renderer(void)
{
}

shared_ptr<Scene> Renderer::AddScene(shared_ptr<Scene> scene)
{
	m_Scenes.push_back(scene);
	return scene;
}

Renderer::~Renderer(void)
{
}
