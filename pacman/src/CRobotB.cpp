//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 29.05.2021.
//

#include "CRobotB.h"

using namespace std;

CRobotB::CRobotB(const CCoord &coord) : CRobot('B', coord) {}

void CRobotB::ChangeDirection(const CMode & mode, const unique_ptr<CPlayer> & player, const CMap & gameMap)
{
    if(m_DeathCount != 0)
        m_Direction = EDirection::NONE;
    else if(mode.IsFrenzy())
        m_Direction = RandomDirection(gameMap);
    else
        m_Direction = BFS(player->Coord(), gameMap);
}




