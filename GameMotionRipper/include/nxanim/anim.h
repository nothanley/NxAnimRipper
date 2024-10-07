#include <vector>
#include <string>
#include <memory>
#pragma once

enum enAnimTag
{
	TBUF = 0x46554254,
	MINA = 0x4D494E41,
	ANIM = 0x414E494D,
};

// Forward declarations
class CAnimTree;

// Class definition
class CGameAnim
{

public:
	CGameAnim();

public:
	const std::vector<std::shared_ptr<CAnimTree>>& trees() const;

protected:
	std::vector<std::shared_ptr<CAnimTree>> m_trees;
};


