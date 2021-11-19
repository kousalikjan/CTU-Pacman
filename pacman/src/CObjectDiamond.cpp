//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 02.06.2021.
//



#include "CObjectDiamond.h"

using namespace std;

CObjectDiamond::CObjectDiamond() : CObject('&') {}

std::unique_ptr<CObject> CObjectDiamond::Clone() const
{
    return make_unique<CObjectDiamond>(*this);
}

bool CObjectDiamond::Interact(CGameState & state) const
{
    state.m_Score+=DIAMOND_VALUE;
    return true;
}


