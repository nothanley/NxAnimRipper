#include <vector>
#include <string>
#include <animstructs.h>
#pragma once

#define NXMATRIX_LEN 0x40

struct NXChannel
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
	uint16_t target() const;
	void load(char* data, const size_t size);
	void setTarget(const uint16_t index);
	std::vector<NXChannel>& channels();

private:
	void parseController(char* data, NXChannel& channel);

private:
	uint16_t m_targetIndex;
	std::vector<NXChannel> m_channels;
};

