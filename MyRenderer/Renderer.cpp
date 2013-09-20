#include "Renderer.h"


Renderer::Renderer(void) :
	m_IsWireFrame(false)
{
}

shared_ptr<IScene> Renderer::AddScene(shared_ptr<IScene> scene)
{
	m_Scenes.push_back(scene);
	return scene;
}

bool Renderer::IsWireFrame() const
{
	return m_IsWireFrame;
}

void Renderer::AsWireFrame(bool is_enabled)
{
	m_IsWireFrame = is_enabled;
}

Renderer::~Renderer(void)
{
}
