#include <nxanimframe.h>
#include <memoryreader.h>

using namespace memreader;

CNXAnimFrame::CNXAnimFrame()
{
}

CNXAnimFrame::~CNXAnimFrame()
{
}

std::vector<NXAnimEntity>& CNXAnimFrame::entities()
{
	return m_entities;
}

bool CNXAnimFrame::empty() const
{
	return m_entities.empty();
}

void CNXAnimFrame::setTrack(const uint16_t index)
{
	this->m_trackIndex = index;
}

void CNXAnimFrame::setKeyIndex(const uint32_t index)
{
	this->m_frameIndex = index;
}

uint16_t CNXAnimFrame::track() const
{
	return m_trackIndex;
}

uint32_t CNXAnimFrame::key() const
{
	return m_frameIndex;
}

void CNXAnimFrame::load(char* data, const size_t size)
{
	if (!data || size <= 0)
		return;

	char* stream    = data;
	int numElements = size / NXMATRIX_LEN;
	this->m_entities.resize(numElements);

	for (int i = 0; i < numElements; i++)
	{
		this->parseController(stream, m_entities[i]);
		m_entities[i].id = i;
		stream += NXMATRIX_LEN;
	}
}

void CNXAnimFrame::parseController(char* data, NXAnimEntity& entity)
{
	if (!data) return;
	auto& matrix = entity.matrix;

	// Load matrices from data stream
	matrix.row3 = NX::Vec4{ ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true) };
	matrix.row2 = NX::Vec4{ ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true) };
	matrix.row1 = NX::Vec4{ ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true) };
	matrix.row0 = NX::Vec4{ ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true) };
}

