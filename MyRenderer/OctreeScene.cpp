#include <queue>

#include "OctreeScene.h"

OctreeScene::OctreeScene(const ColorRGBA& background_color, unsigned max_tree_depth) :
	Scene(background_color),
	m_GeometryTree(max_tree_depth)
{
}

void OctreeScene::OnInitialize()
{
	m_GeometryTree.Initialize(m_Geometries);
}

bool OctreeScene::Intersect(const Ray& ray, Intersection& intersection, void* additional_data) const
{
	float min_t = ray.EffectRange().Max;
	const OctreeNode* current = m_GeometryTree.Root();
	std::priority_queue<Octree::QueueElement> queue;
	Intersection hit;

	if (current->Extents().Intersect(ray, hit, additional_data))
		queue.push(Octree::QueueElement(hit.Distance(), current));

	while (!queue.empty() && queue.top().t < min_t)
	{
		current = queue.top().node;
		queue.pop();

		if (current->IsLeaf())
		{
			for (auto iter = current->Objects().begin(); iter != current->Objects().end(); ++iter)
			{
				if ((*iter)->Intersect(ray, hit, additional_data) && hit.Distance() < min_t)
				{
					min_t = hit.Distance();
					intersection = hit;
				}
			}
		}
		else
		{
			for (unsigned i = 0; i < 8; ++i)
				if (current->ChildAt(i) != nullptr)
					if (current->ChildAt(i)->Extents().Intersect(ray, hit, additional_data))
						queue.push(Octree::QueueElement(hit.Distance(), current->ChildAt(i)));
		}
	}

	if (min_t != ray.EffectRange().Max)
		return true;
	else
		return false;
}

OctreeScene::~OctreeScene(void)
{
}
