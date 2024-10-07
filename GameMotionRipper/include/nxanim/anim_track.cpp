#include <anim_track.h>

CAnimTrack::CAnimTrack()
	:
	m_trackId(0),
	m_numKeys(0),
	m_hasRotation(false),
	m_hasTranslation(false)
{
}

CAnimTrack::~CAnimTrack()
{
}

const std::vector<NX::KeyFrame>& 
CAnimTrack::posKeys() const
{
	return m_translateKeys;
}

const std::vector<NX::KeyFrame>&
CAnimTrack::rotKeys() const
{
	return m_rotationKeys;
}

uint32_t
CAnimTrack::id() const
{
	return m_trackId;
}

