//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 28.05.2021.
//

#include "CObjectGold.h"

using namespace std;

CObjectGold::CObjectGold() : CObject('.') {}

unique_ptr<CObject> CObjectGold::Clone() const
{
    return make_unique<CObjectGold>(*this);
}

bool CObjectGold::Interact(CGameState & state) const
{
    state.m_Score++;
    return true;
}

