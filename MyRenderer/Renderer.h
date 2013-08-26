#pragma once

#include "Scene.h"

class Renderer
{
public:
	Renderer(void);

	shared_ptr<Scene> AddScene(shared_ptr<Scene> scene);

	virtual void Render() const = 0;

	virtual ~Renderer(void) = 0;

protected:
	List(Scene) m_Scenes;
};

