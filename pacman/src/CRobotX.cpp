//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date  31.05.2021.
//


#include "CRobotX.h"

using namespace std;

CRobotX::CRobotX(const CCoord & coord) : CRobot('X', coord) {}

void CRobotX::ChangeDirection(const CMode & mode, const unique_ptr<CPlayer> & player, const CMap & gameMap)
{
    if(m_DeathCount != 0)
        m_Direction = EDirection::NONE;
    else if(mode.IsFrenzy())
        m_Direction = RandomDirection(gameMap);
    else if (mode.GetDifficulty() == EDifficulty::EASY)
        m_Direction = player->Direction();
    else
        m_Direction = BFS(player->Coord(), gameMap);
}
