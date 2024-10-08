#include <vector>
#include <string>
#include <animstructs.h>
#pragma once

#define NXMATRIX_LEN 0x40

struct NXAnimEntity
{
	uint32_t id;
	NX::NXMatrix4 matrix;
};

class CNXAnimFrame
{
public:
	CNXAnimFrame();
	~CNXAnimFrame();

public:
	bool empty() const;
	uint32_t key() const;
	uint16_t track() const;
	void load(char* data, const size_t size);
	void setKeyIndex(const uint32_t index);
	void setTrack(const uint16_t index);
	std::vector<NXAnimEntity>& entities();

private:
	void parseController(char* data, NXAnimEntity& entity);

private:
	uint32_t m_frameIndex; // defines which keyframe to use
	uint16_t m_trackIndex; // defines which track to use
	std::vector<NXAnimEntity> m_entities;
};

