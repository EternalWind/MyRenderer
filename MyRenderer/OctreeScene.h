#pragma once

#include "Scene.h"
#include "Octree.h"

class OctreeScene :
	public Scene
{
public:
	OctreeScene(const ColorRGBA& background_color = ColorRGBA(), unsigned max_tree_depth = 16);
	
	bool Intersect(const Ray& ray, Intersection& intersection, void* additional_data = nullptr) const;
	
	~OctreeScene(void);

protected:
	void OnInitialize();

private:
	Octree m_GeometryTree;
};

