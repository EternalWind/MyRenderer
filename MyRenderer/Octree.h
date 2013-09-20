#pragma once

#include <array>
#include <vector>

#include "Defs.h"
#include "Object.h"
#include "Volume.h"

using namespace std;

class OctreeNode
{
public:
	OctreeNode(unsigned depth);

	const OctreeNode* ChildAt(unsigned i) const;

	const array<OctreeNode*, 8>& Children() const;

	bool IsLeaf() const;

	const vector <shared_ptr<Object> >& Objects() const;

	unsigned Depth() const;

	const Volume& Extents() const;

	~OctreeNode();

private:
	array<OctreeNode*, 8> m_Children;
	bool m_IsLeaf;
	vector < shared_ptr<Object> > m_Objects;
	unsigned m_Depth;
	Volume m_Extents;

	friend class Octree;
};

class Octree
{
public:
	struct QueueElement
	{
		float t;
		const OctreeNode* node;

		QueueElement(float distance, const OctreeNode* octree_node);
		bool operator < (const QueueElement& other) const;
	};

	Octree(unsigned max_depth = 16);

	void Initialize(const List(Object)& objects);

	const OctreeNode* Root() const;

	unsigned MaxDepth() const;

	~Octree(void);

private:
	void Build(OctreeNode* node);

	void Insert(shared_ptr<Object> object);

	void ComputeChildBounds(unsigned child_index, const Vector3& center, const Vector3& min_bound, const Vector3& max_bound,
		Vector3& child_min_bound, Vector3& child_max_bound) const;

	bool m_IsInitialized;
	Vector3 m_MinBound;
	Vector3 m_MaxBound;
	OctreeNode* m_Root;
	unsigned m_MaxDepth;
};

// Implementations for inline methods.

inline const OctreeNode* OctreeNode::ChildAt(unsigned i) const
{
	if (i > 7)
		throw Exception("Tried to access the 9th child of an octree which only has 8 children.");

	return m_Children[i];
}

inline const array<OctreeNode*, 8>& OctreeNode::Children() const
{
	return m_Children;
}

inline bool OctreeNode::IsLeaf() const
{
	return m_IsLeaf;
}

inline const vector< shared_ptr<Object> >& OctreeNode::Objects() const
{
	return m_Objects;
}

inline unsigned OctreeNode::Depth() const
{
	return m_Depth;
}

inline const Volume& OctreeNode::Extents() const
{
	return m_Extents;
}

inline const OctreeNode* Octree::Root() const
{
	return m_Root;
}

inline Octree::QueueElement::QueueElement(float distance, const OctreeNode* octree_node) :
    t(distance),
	node(octree_node)
{}

inline bool Octree::QueueElement::operator < (const QueueElement& other) const
{
	return t > other.t;
}