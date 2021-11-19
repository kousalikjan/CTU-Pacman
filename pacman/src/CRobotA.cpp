//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 29.05.2021.
//

#include "CRobotA.h"

using namespace std;

CRobotA::CRobotA(const CCoord &coord) : CRobot('A', coord) {}

void CRobotA::ChangeDirection(const CMode & mode, const unique_ptr<CPlayer> & player, const CMap & gameMap)
{
    if(m_DeathCount != 0)
        m_Direction = EDirection::NONE;
    else if(mode.GetDifficulty() == EDifficulty::EASY || mode.IsFrenzy())
        m_Direction = RandomDirection(gameMap);
    else
        m_Direction = BFS(player->Coord(), gameMap);
}


