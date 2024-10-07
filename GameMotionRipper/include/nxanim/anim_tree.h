#include <vector>
#include <string>
#include <memory>
#pragma once

//Forward declarations
class CAnimNode;

// Class definition
class CAnimTree
{
public:
	CAnimTree();
	
public:
	std::shared_ptr<CAnimNode> node() const;
	uint64_t guid() const;
	int16_t flag() const;

protected:
	std::shared_ptr<CAnimNode> m_node;

protected:
	uint64_t m_guid;
	int16_t  m_flag;
	uint32_t m_version;
	uint32_t m_size;
};

