//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 28.05.2021.
//

#include "CPlayer.h"

using namespace std;

CPlayer::CPlayer(const CCoord & coord) : CCharacter('@', coord), m_Lives(2) {}

void CPlayer::SetDirection(const EDirection & direction)
{
    m_Direction = direction;
    m_Value = NewValue();
}

char CPlayer::NewValue()
{
    switch (m_Direction)
    {
        case EDirection::UP: return '^';
        case EDirection::LEFT: return '<';
        case EDirection::DOWN: return 'v';
        case EDirection::RIGHT: return '>';
        default: return '@';
    }
}

bool CPlayer::IsDead() const
{
    return m_Lives == 0;
}

size_t CPlayer::GetLives() const
{
    return m_Lives;
}

void CPlayer::Collision(bool frenzy)
{
    if(!frenzy)
        m_Lives--;
}



