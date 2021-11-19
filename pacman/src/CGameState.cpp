//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 28.05.2021.
//

#include "CGameState.h"

using namespace std;


CGameState::CGameState(const CCoord & playerCoord, CConfig config, size_t targetScore) :
    m_TargetScore(targetScore),
    m_Player(make_unique<CPlayer>(CPlayer(playerCoord))),
    m_Config(move(config)),
    m_Mode(m_Config, false),
    m_Score(0) {}

size_t CGameState::GetTargetScore() const
{
    return m_TargetScore;
}


