#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include <animstructs.h>
#pragma once

struct BitVecInfo
{
	uint16_t x;
	uint16_t y;
	uint16_t z;
	uint16_t w;

	BitVecInfo(uint16_t magic);
	size_t length();
};

static std::vector<uint32_t> gStepLvl
{
	0x1E, 0x14, 0x0F, 0x0C,
	0x0A, 0x06, 0x05, 0x04,
	0x03, 0x02, 0x01, 0x00
};

namespace bitstream 
{
	int32_t extractBitsNew(char* data, uint32_t& byteOffset, uint32_t& bitOffset, uint16_t& numBits);
	int32_t extractBits(const uint8_t* data, uint32_t& bitOffset, uint32_t numBits);
	void    calcTfmQuaternion(NX::Vec4& v);
}

class BitStreamReader {
public:
    BitStreamReader(const char* stream)
        : stream_(stream), byteOffset_(0), bitOffset_(0) {}

    // Function to read 'n' bits from the bitstream and return them as int32_t
    int32_t readBits(uint8_t bitLength) 
    {
        int32_t result = 0;
        uint8_t bitsRemaining = bitLength;

        while (bitsRemaining > 0)
        {
            // Get the current byte and shift to account for the current bit offset.
            uint8_t currentByte = static_cast<uint8_t>(stream_[byteOffset_]);
            currentByte >>= bitOffset_;

            // Determine how many bits we can read from the current byte.
            uint8_t bitsAvailable = 8 - bitOffset_;
            uint8_t bitsToRead = std::min(bitsAvailable, bitsRemaining);

            // Mask and extract the bits to read.
            uint8_t mask = (1 << bitsToRead) - 1;
            result |= (currentByte & mask) << (bitLength - bitsRemaining);

            // Update the offsets.
            bitsRemaining -= bitsToRead;
            bitOffset_ += bitsToRead;

            // If we've read all the bits in the current byte, move to the next one.
            if (bitOffset_ == 8) {
                bitOffset_ = 0;
                ++byteOffset_;
            }
        }

        return result;
    }

    // Function to reset the stream position
    void reset() {
        byteOffset_ = 0;
        bitOffset_ = 0;
    }

    // Function to get the current byte offset
    size_t getByteOffset() const {
        return byteOffset_;
    }

    // Function to get the current bit offset within the byte
    uint8_t getBitOffset() const {
        return bitOffset_;
    }

private:
    const char* stream_;
    size_t byteOffset_;  // Current byte offset in the stream
    uint8_t bitOffset_;  // Current bit offset within the current byte
};
