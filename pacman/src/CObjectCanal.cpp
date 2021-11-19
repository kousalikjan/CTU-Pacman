//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 28.05.2021.
//



#include "CObjectCanal.h"

using namespace std;

CObjectCanal::CObjectCanal(const CCoord &coord) : CObject('0'), m_Destination(coord) {}

unique_ptr<CObject> CObjectCanal::Clone() const
{
    return make_unique<CObjectCanal>(*this);
}

bool CObjectCanal::Interact(CGameState & state) const
{
    state.m_Player->SetCoord(m_Destination);
    return false;
}
