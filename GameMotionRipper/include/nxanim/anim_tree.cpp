#include <anim_tree.h>

CAnimTree::CAnimTree()
	:
	m_guid(0),
	m_flag(0),
	m_version(0),
	m_size(0)
{
}

std::shared_ptr<CAnimNode> 
CAnimTree::node() const
{
	return m_node;
}

uint64_t
CAnimTree::guid() const
{
	return m_guid;
}

int16_t
CAnimTree::flag() const
{
	return m_flag;
}

