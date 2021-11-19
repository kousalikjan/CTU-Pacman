//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 28.05.2021.
//



#include "CObjectCherry.h"

using namespace std;

CObjectCherry::CObjectCherry() : CObject('$') {}

unique_ptr<CObject> CObjectCherry::Clone() const
{
    return make_unique<CObjectCherry>(*this);
}

bool CObjectCherry::Interact(CGameState & state) const
{
    state.m_Mode = CMode(state.m_Config, true);
    return true;
}

