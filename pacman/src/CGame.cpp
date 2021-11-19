//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 29.05.2021.
//

#include "CGame.h"

#include "CRobotA.h"
#include "CRobotB.h"
#include "CRobotX.h"

#include "game_exit.h"


using namespace std;

CGame::CGame(CMap map, CGameState state, const shared_ptr<CInterface> & interface) :
m_Map(move(map)), m_State(move(state)),
m_Interface(interface), m_Active(true), m_Win(false)
{
    m_Robots.push_back(make_unique<CRobotA>(CRobotA(m_Map.GetStartingCoords(ECharacter::ROBOTA))));
    m_Robots.push_back(make_unique<CRobotB>(CRobotB(m_Map.GetStartingCoords(ECharacter::ROBOTB))));
    m_Robots.push_back(make_unique<CRobotX>(CRobotX(m_Map.GetStartingCoords(ECharacter::ROBOTX))));
}

void CGame::Run()
{
    m_Interface->InitializeBuffer(m_Map);
    CheckObjects();
    RedrawInterface();
    while(m_Active)
    {
        if(!MovePlayer()) break;
        if(CheckCollisions()) break;
        CheckObjects();
        if(GameWin()) break;
        if(CheckCollisions()) break;
        MoveRobots();
        if(CheckCollisions()) break;
        AddCherry();
        CheckMode();
        TickDeathCount();
        RedrawInterface();
    }
}

void CGame::RedrawInterface() const
{
    m_Interface->Clear()
    .PrintState(m_State)
    .DrawObjects(m_Map)
    .DrawWalls(m_Map)
    .DrawCharacter(*m_State.m_Player);
    for (const auto & robot : m_Robots)
        m_Interface->DrawCharacter(*robot);
    m_Interface->FlushBuffer();
}

bool CGame::CheckCollisions()
{
    for (const auto & robot : m_Robots)
    {
        if (robot->Coord() == m_State.m_Player->Coord())
        {
            m_State.m_Player->Collision(m_State.m_Mode.IsFrenzy());
            if(m_State.m_Player->IsDead())
            {
                m_Active = false;
                return true;
            }
            robot->Reset();
            RedrawInterface();
        }
    }
    return false;
}

void CGame::CheckObjects()
{
    m_Map.InteractObjects(m_State);
}

void CGame::MoveCharacter(CCharacter & character) const
{
    if(!m_Map.IsWall(character.Coord() + character.Direction()))
        character.SetCoord(character.Coord() + character.Direction());
}

bool CGame::MovePlayer()
{
    try
    {
        m_State.m_Player->SetDirection(m_Interface->PromptDirection());
    }
    catch(const game_exit & e)
    {
        m_Active = false;
        return false;
    }
    MoveCharacter(*m_State.m_Player);
    return true;
}

void CGame::MoveRobots() const
{
    for(const auto & robot : m_Robots)
    {
        robot->ChangeDirection(m_State.m_Mode, m_State.m_Player, m_Map);
        MoveCharacter(*robot);
    }
}

void CGame::CheckMode()
{
    if(m_State.m_Mode.DecTime().GetTime() == 0)
    {
        bool wasFrenzy = m_State.m_Mode.IsFrenzy();
        m_State.m_Mode = CMode(m_State.m_Config, !wasFrenzy);
    }
}

bool CGame::GameWin()
{
    if (m_State.m_Score == m_State.GetTargetScore())
    {
        m_Win = true;
        m_Active = false;
        return true;
    }
    return false;
}

void CGame::End() const
{
    if(m_Win)
        m_Interface->PrintWin();
    else
        m_Interface->PrintDefeat(m_State);
}

void CGame::AddCherry()
{
    if(SRandom::RandomIdx(100) < m_State.m_Config.GetProbability())
        m_Map.AddCherry();
}

void CGame::TickDeathCount()
{
    for (const auto & robot : m_Robots)
        robot->TickDeathCount();
}
