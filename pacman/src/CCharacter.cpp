//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 28.05.2021.
//

#include "CCharacter.h"

using namespace std;


CCharacter::CCharacter(char value, const CCoord &coord) : m_Value(value) , m_Coord(coord), m_Direction(EDirection::NONE) {}

const CCoord & CCharacter::Coord() const
{
    return m_Coord;
}

EDirection CCharacter::Direction() const
{
    return m_Direction;
}

void CCharacter::SetCoord(const CCoord &coord)
{
    m_Coord = coord;
}

char CCharacter::Value() const
{
    return m_Value;
}

