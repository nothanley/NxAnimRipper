#include <vector>
#include <string>
#include <memory>
#include <animstructs.h>
#pragma once 

struct Vec4;

class CAnimTrack
{
public:
	CAnimTrack();
	~CAnimTrack();

public:
	uint32_t id() const;
	const std::vector<NX::KeyFrame>& posKeys() const;
	const std::vector<NX::KeyFrame>& rotKeys() const;

protected:
	std::vector<NX::KeyFrame> m_rotationKeys;
	std::vector<NX::KeyFrame> m_translateKeys;
	uint32_t m_trackId;
	uint32_t m_numKeys;
	bool m_hasRotation;
	bool m_hasTranslation;
};

