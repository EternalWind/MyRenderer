#include "Octree.h"
#include "Mesh.h"

OctreeNode::OctreeNode(unsigned depth) :
	m_IsLeaf(true),
	m_Depth(depth)
{
	for (unsigned i = 0; i < 8; ++i)
		m_Children[i] = nullptr;
}

OctreeNode::~OctreeNode()
{
	for (unsigned i = 0; i < 8; ++i)
		if (m_Children[i] != nullptr)
			delete m_Children[i];
}

Octree::Octree(unsigned max_depth) :
	m_IsInitialized(false),
	m_Root(new OctreeNode(0)),
	m_MaxDepth(max_depth)
{
}

void Octree::Initialize(const List(Object)& objects)
{
	if (!m_IsInitialized)
	{
		Volume scene_extents;

		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
			scene_extents.ExtendBy((*iter)->BoundingVolume().get());

		m_MinBound = scene_extents.MinExtent();
		m_MaxBound = scene_extents.MaxExtent();

		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			Insert(*iter);
		}

		Build(m_Root);

		m_IsInitialized = true;
	}

#ifdef DEBUG
	assert(m_MinBound == m_Root->m_Extents.MinExtent());
	assert(m_MaxBound == m_Root->m_Extents.MaxExtent());
#endif
}

unsigned Octree::MaxDepth() const
{
	return m_MaxDepth;
}

Octree::~Octree(void)
{
	if (m_Root != nullptr)
		delete m_Root;
}

void Octree::Build(OctreeNode* node)
{
	if (node->m_IsLeaf)
		for (auto iter = node->m_Triangles.begin(); iter != node->m_Triangles.end(); ++iter)
		{
			unsigned num_vertices[1] = { 3 };
			Vector3 vertices[3] = { (*iter)->Vertex(0), (*iter)->Vertex(1), (*iter)->Vertex(2) };
			Mesh triangle_mesh(1, num_vertices, vertices);
			triangle_mesh.Initialize();

			node->m_Extents.ExtendBy(triangle_mesh.BoundingVolume().get());
		}
	else
		for (unsigned i = 0; i < 8; ++i)
			if (node->m_Children[i] != nullptr)
			{
				Build(node->m_Children[i]);
				node->m_Extents.ExtendBy(&(node->m_Children[i]->m_Extents));
			}
}

void Octree::Insert(shared_ptr<Object> object)
{
	auto triangles = object->Triangles();

	for (auto iter = triangles.begin(); iter != triangles.end(); ++iter)
	{
		Insert(*iter);
	}
}

void Octree::Insert(shared_ptr<Triangle> triangle)
{
	OctreeNode* current = m_Root;
	Vector3 min_bound = m_MinBound;
	Vector3 max_bound = m_MaxBound;

	while (current->m_Depth < m_MaxDepth)
	{
		if (current->m_IsLeaf)
		{
			if (current->m_Triangles.size() == 0)
			{
				break;
			}
			else
			{
				current->m_IsLeaf = false;

				for (auto iter = current->m_Triangles.begin(); iter != current->m_Triangles.end(); ++iter)
				{
					Insert(*iter);
				}

				current->m_Triangles.clear();
			}
		}
		else
		{
			Vector3 node_center = (max_bound + min_bound) * 0.5f;
			Vector3 object_center = (triangle->MaxExtent() + triangle->MinExtent()) * 0.5f;
			unsigned child_index = 0;

			if (object_center.X() < node_center.X())
				child_index += 4;
			if (object_center.Y() < node_center.Y())
				child_index += 2;
			if (object_center.Z() < node_center.Z())
				child_index += 1;

			if (current->m_Children[child_index] == nullptr)
				current->m_Children[child_index] = new OctreeNode(current->m_Depth + 1);

			current = current->m_Children[child_index];

			ComputeChildBounds(child_index, node_center, min_bound, max_bound, min_bound, max_bound);
		}
	}

	current->m_Triangles.push_back(triangle);
}

void Octree::ComputeChildBounds(unsigned child_index, const Vector3& center, const Vector3& min_bound, const Vector3& max_bound,
								Vector3& child_min_bound, Vector3& child_max_bound) const
{
	child_min_bound.SetX((child_index & 4) ? min_bound.X() : center.X());
	child_min_bound.SetY((child_index & 2) ? min_bound.Y() : center.Y());
	child_min_bound.SetZ((child_index & 1) ? min_bound.Z() : center.Z());

	child_max_bound.SetX((child_index & 4) ? center.X() : max_bound.X());
	child_max_bound.SetY((child_index & 2) ? center.Y() : max_bound.Y());
	child_max_bound.SetZ((child_index & 1) ? center.Z() : max_bound.Z());
}