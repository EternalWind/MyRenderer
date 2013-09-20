#pragma once

#include "IScene.h"

class Renderer
{
public:
	Renderer(void);

	shared_ptr<IScene> AddScene(shared_ptr<IScene> scene);

	virtual void Render() const = 0;

	bool IsWireFrame() const;

	void AsWireFrame(bool is_enabled);

	virtual ~Renderer(void) = 0;

protected:
	List(IScene) m_Scenes;
	bool m_IsWireFrame;
};

