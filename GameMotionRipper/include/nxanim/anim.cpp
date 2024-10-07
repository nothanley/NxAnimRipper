#include <anim.h>

CGameAnim::CGameAnim()
{
}

const std::vector<std::shared_ptr<CAnimTree>>& 
CGameAnim::trees() const
{
	return m_trees;
}

