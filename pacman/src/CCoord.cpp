//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 29.05.2021.
//

#include "CCoord.h"

CCoord::CCoord() : m_Y(0), m_X(0) {}

CCoord::CCoord(size_t y, size_t x) : m_Y(y), m_X(x) {}

bool CCoord::operator == (const CCoord &rhs) const
{
    return m_X == rhs.m_X && m_Y == rhs.m_Y;
}

bool CCoord::operator!=(const CCoord &rhs) const
{
    return !(*this == rhs);
}

bool CCoord::operator < (const CCoord &rhs) const
{
    if(m_Y != rhs.m_Y)
        return m_Y < rhs.m_Y;
    return m_X < rhs.m_X;
}

CCoord CCoord::operator + (const EDirection &direction) const
{
    CCoord res = *this;
    switch(direction)
    {
        case EDirection::UP:
            res.m_Y--;
            break;
        case EDirection::RIGHT:
            res.m_X++;
            break;
        case EDirection::LEFT:
            res.m_X--;
            break;
        case EDirection::DOWN:
            res.m_Y++;
            break;
        case EDirection::NONE:
            break;
    }
    return res;
}



