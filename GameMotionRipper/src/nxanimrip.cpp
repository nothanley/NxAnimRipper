#include <nxanimrip.h>
#include <memoryreader.h>

using namespace memreader;

CNXAnimFrame::CNXAnimFrame()
{
}

CNXAnimFrame::~CNXAnimFrame()
{
}

std::vector<NXChannel>& CNXAnimFrame::channels()
{
	return m_channels;
}

bool CNXAnimFrame::empty() const
{
	return m_channels.empty();
}

void CNXAnimFrame::load(char* data, const size_t size)
{
	if (!data || size <= 0)
		return;

	char* stream    = data;
	int numElements = size / NXMATRIX_LEN;
	this->m_channels.resize(numElements);

	for (int i = 0; i < numElements; i++)
	{
		this->parseController(stream, m_channels[i]);
		m_channels[i].id = i;
		stream += NXMATRIX_LEN;
	}
}

void CNXAnimFrame::parseController(char* data, NXChannel& channel)
{
	if (!data) return;
	auto& matrix = channel.matrix;

	// Load matrices from data stream
	matrix.row3 = NX::Vec4{ ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true) };
	matrix.row2 = NX::Vec4{ ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true) };
	matrix.row1 = NX::Vec4{ ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true) };
	matrix.row0 = NX::Vec4{ ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true), ReadFloat(data, true) };
}

