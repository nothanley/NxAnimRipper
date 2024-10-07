#include <anim_node.h>

CAnimNode::CAnimNode()
	:
	m_hash(0),
	m_numKeys(0),
	m_numTracks(0)
{
}

const std::vector<std::shared_ptr<CAnimTrack>>&
CAnimNode::tracks() const
{
	return m_tracks;
}

uint32_t
CAnimNode::numKeys() const
{
	return m_numKeys;
}

