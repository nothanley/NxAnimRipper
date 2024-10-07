#include <vector>
#include <string>
#include <memory>
#pragma once

// Forward declarations
class CAnimTrack;

// Class definition
class CAnimNode
{
public:
	CAnimNode();

public:
	uint32_t numKeys() const;
	const std::vector<std::shared_ptr<CAnimTrack>>& tracks() const;

protected:
	std::vector<std::shared_ptr<CAnimTrack>> m_tracks;

protected:
	uint32_t m_hash;
	uint32_t m_numKeys;
	uint32_t m_numTracks;
};

