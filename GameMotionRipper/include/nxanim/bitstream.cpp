#include <bitstream.h>
#include <memoryreader.h>

using namespace memreader;

BitVecInfo::BitVecInfo(uint16_t magic)
{
	x = ((magic >> 0xA) & 0x1F) + 1;
	y = ((magic >> 0x5) & 0x1F) + 1;
	z = (magic & 0x1F) + 1;
	w = 0x1 + 1;
}

size_t 
BitVecInfo::length()
{
	return (x + y + z + w);
}

int32_t 
bitstream::extractBits(const uint8_t* data, uint32_t& bitOffset, uint32_t numBits)
{
	uint32_t result = 0;
	uint32_t byteOffset = bitOffset / 8;
	uint32_t bitShift   = bitOffset % 8;

	for (uint32_t i = 0; i < numBits; ++i)
	{
		uint32_t byte = (data[byteOffset] >> bitShift) & 1;
		result |= (byte << i);
		bitOffset++;
		byteOffset = bitOffset / 8;
		bitShift   = bitOffset % 8;
	}

	return *reinterpret_cast<int32_t*>(&result);
}

void
bitstream::calcTfmQuaternion(NX::Vec4& tfm)
{
    NX::Vec4 quat;
    int shuffle  = tfm.w;
    float elem   = 1.0f - (tfm.x * tfm.x + tfm.y * tfm.y + tfm.z * tfm.z);
    elem         = (elem < 0.0f) ? 0.0f : sqrt(elem);

    switch (shuffle) 
    {
        case 3: /* Level 4 */
            quat.w = elem;
            quat.z = tfm.x;   
            quat.y = tfm.z;   
            quat.x = tfm.y;   
            break;
        case 2: /* Level 3 */
            quat.w = tfm.x;   
            quat.z = elem;
            quat.y = tfm.z;   
            quat.x = tfm.y;   
            break;
        case 1: /* Level 2 */
            quat.w = tfm.x;   
            quat.z = tfm.z;   
            quat.y = elem;
            quat.x = tfm.y;   
            break;
        case 0: /* Level 1 */
            quat.w = tfm.x;  
            quat.z = tfm.z;  
            quat.y = tfm.y;  
            quat.x = elem;
            break;
        default:
            break;
    }

    // update transform
    tfm = quat;
}


int32_t bitstream::extractBitsNew(char* data, uint32_t& byteOffset, uint32_t& bitOffset, uint16_t& numBits)
{
    uint32_t value;
    uint32_t result = 0x0;
    uint16_t remaining = numBits;

    while (remaining > 0) 
    {
        data += byteOffset;
        uint16_t numBits = std::min<uint16_t>(0x8 - bitOffset, remaining);

        value = uint16_t(ReadUInt8(data));
        value >>= bitOffset;
        value &= ((0x1 << numBits) - 1);
        value <<= (numBits - remaining);

        bitOffset += numBits;
        result |= value;
        byteOffset += (bitOffset >> 0x3);
        bitOffset &= 0x7;
        remaining -= numBits;
    }

    return *reinterpret_cast<int32_t*>(&result);
}
