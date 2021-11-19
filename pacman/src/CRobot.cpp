//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 29.05.2021.
//

#include "CRobot.h"

#include <map>
#include <queue>

using namespace std;


CRobot::CRobot(char val, const CCoord & coord) : CCharacter(val, coord), m_StartingCoords(coord), m_DeathCount(0) {}

void CRobot::Reset()
{
    m_DeathCount = DEATH_COUNT;
    m_Coord = m_StartingCoords;
}

void CRobot::TickDeathCount()
{
    if(m_DeathCount > 0)
        m_DeathCount--;
}


EDirection CRobot::BFS(const CCoord & target, const CMap & gameMap) const
{
    map<CCoord, pair<CCoord, EDirection>> visited;
    queue<CCoord> toVisit;
    visited.insert({Coord(), {{static_cast<size_t>(-1), static_cast<size_t>(-1)}, EDirection::NONE}});
    toVisit.push(Coord());

    while(!toVisit.empty())
    {
        CCoord from = toVisit.front();
        toVisit.pop();
        for (size_t i = 0; i < DIRECTIONS; ++i)
        {
            auto dir = static_cast<EDirection>(i);
            CCoord to = from + dir;
            if(!gameMap.IsWall(to) && visited.insert({to, {from, dir}}).second)
                toVisit.push(to);
        }
    }

    auto it = visited.find(target);
    if(it == visited.end())
        throw runtime_error("Player is unreachable!");
    while(it->second.first != Coord())
        it = visited.find(it->second.first);
    return it->second.second;
}

EDirection CRobot::RandomDirection(const CMap & map) const
{
    EDirection dir;
    do
        dir = SRandom::RandomDireciton();
    while (map.IsWall(Coord() + dir));
    return dir;
}





