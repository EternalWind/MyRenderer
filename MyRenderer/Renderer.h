#pragma once

#include "Scene.h"

class Renderer
{
public:
	Renderer(void);

	shared_ptr<Scene> AddScene(shared_ptr<Scene> scene);

	virtual void Render() const = 0;

	bool IsWireFrame() const;

	void AsWireFrame(bool is_enabled);

	virtual ~Renderer(void) = 0;

protected:
	List(Scene) m_Scenes;
	bool m_IsWireFrame;
};

