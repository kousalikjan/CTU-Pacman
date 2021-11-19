//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 08.05.2021.
//

#include <limits>

#include "CInterface.h"
#include "game_exit.h"

using namespace std;

CInterface::CInterface(istream & in, ostream & out) : m_In(in), m_Out(out)
{
    m_In.exceptions(ios::badbit | ios::failbit);
    m_Out.exceptions(ios::failbit | ios::badbit);
}

CInterface & CInterface::PrintMessage(const string & message, EColors color)
{
    PrepareColor(color).m_Out << message;
    return *this;
}

CInterface & CInterface::PrintNewLine()
{
    m_Out << '\n';
    return *this;
}

CInterface &CInterface::PrintBar(size_t length, EColors color)
{
    PrepareColor(color);
    for (size_t i = 0; i < length; ++i)
        m_Out << '-';
    return *this;
}

CInterface & CInterface::PrintMainMenu()
{
    PrintMessage("Robocop 2021\n", EColors::RED)
    .PrintMessage("Type ").PrintMessage("help", EColors::BLUE).PrintMessage(" for instructions\n");
    return *this;
}

ECommand CInterface::PromptCommand()
{
    PrintMessage("Enter command: ");
    string tmp;
    m_In >> tmp;
    m_In.ignore(numeric_limits<streamsize>::max(), '\n');
    if(tmp == "new") return ECommand::NEW;
    if(tmp == "help") return ECommand::HELP;
    if(tmp == "quit") return ECommand::QUIT;
    return ECommand::ERROR;
}

std::string CInterface::PromptMapFilename()
{
    PrintMessage("Select a map (type an index)\n", EColors::BLUE).
    PrintMessage("[0 -> City]\n"
                 "[1 -> Metro]\n"
                 "[2 -> Space]\n"
                 "[3-9 -> Unfinished]\n"
                 "[10 -> Unreachable]\n");
    return m_MapNames[PromptIndex(MAP_INDEXES)];
}
std::string CInterface::PromptConfigFilename()
{
    PrintMessage("Select a difficulty (type an index)\n", EColors::BLUE)
    .PrintMessage("[0 -> Easy]\n"
                 "[1 -> Hard]\n"
                 "[2-5 -> Unfinished]\n");
    return m_ConfigNames[PromptIndex(CONFIG_INDEXES)];
}

EDirection CInterface::PromptDirection()
{
    string tmp = "0";
    while(tmp == "0")
    {
        PrintMessage("Enter direction: ");
        m_In >> tmp;
        if(tmp.length() != 1)
        {
            tmp = "0";
            PrintDirectionHelp();
            continue;
        }
        m_In.clear();
        m_In.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(tmp[0])
        {
            case 'w': return EDirection::UP;
            case 'a': return EDirection::LEFT;
            case 's': return EDirection::DOWN;
            case 'd': return EDirection::RIGHT;
            case 'p': throw game_exit();
            default: tmp = "0"; PrintDirectionHelp(); break;
        }
    }
    return EDirection::NONE;
}

size_t CInterface::PromptIndex(int max)
{
    int res = -1;
    while(res < 0 || res > max)
    {
        PrintMessage("Enter index: ");
        try { m_In >> res; }
        catch(const ios_base::failure & e)
        {
            if(m_In.eof())
                throw ios_base::failure("EOF during index prompting!");
            res = -1;
        }
        if(res < 0 || res > max)
        {
            PrintMessage("Enter a valid index!\n", EColors::RED);
            m_In.clear();
            res = -1;
        }
        m_In.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return res;
}


CInterface & CInterface::PrintMenuHelp()
{
    PrintBar()
    .PrintNewLine()
    .PrintMessage("Type ").PrintMessage("new", EColors::BLUE).PrintMessage(" to start a new game\n")
    .PrintMessage("Type ").PrintMessage("quit", EColors::BLUE).PrintMessage(" to exit the application\n")
    .PrintMessage("Type ").PrintMessage("wsad", EColors::BLUE).PrintMessage(" to move during the game\n")
    .PrintBar()
    .PrintNewLine();
    return *this;
}

CInterface & CInterface::PrintWin()
{
    Clear();
    PrintBar()
    .PrintNewLine()
    .PrintMessage("Congratulations!\n", EColors::GREEN)
    .PrintMessage("You have won the game!\n")
    .PrintMessage("Press ").PrintMessage("ANY", EColors::BLUE).PrintMessage(" key to continue\n")
    .PrintBar();
    m_In.get();
    m_In.ignore(numeric_limits<streamsize>::max(), '\n');
    Clear()
    .PrintMainMenu();
    return *this;
}

CInterface & CInterface::PrintDefeat(const CGameState & state)
{
    Clear();
    PrintBar()
    .PrintNewLine()
    .PrintMessage("GAME OVER\n", EColors::RED)
    .PrintMessage("You have gathered ")
    .PrintMessage(to_string(state.m_Score), EColors::GREEN)
    .PrintMessage(" out of ")
    .PrintMessage(to_string(state.GetTargetScore()), EColors::MAGENTA)
    .PrintMessage(" coins!\n")
    .PrintMessage("Press ").PrintMessage("ANY", EColors::BLUE).PrintMessage(" key to continue\n")
    .PrintBar()
    .PrepareColor(EColors::RESET)
    .PrintNewLine();
    m_In.get();
    m_In.ignore(numeric_limits<streamsize>::max(), '\n');
    Clear()
    .PrintMainMenu();
    return *this;
}

CInterface & CInterface::PrintDirectionHelp()
{
    PrintBar(19)
    .PrintNewLine()
    .PrintMessage("Invalid direction!\n", EColors::RED)
    .PrintMessage("w", EColors::BLUE).PrintMessage(" -> UP\n")
    .PrintMessage("a", EColors::BLUE).PrintMessage(" -> LEFT\n")
    .PrintMessage("s", EColors::BLUE).PrintMessage(" -> DOWN\n")
    .PrintMessage("d", EColors::BLUE).PrintMessage(" -> RIGHT\n")
    .PrintMessage("p", EColors::BLUE).PrintMessage(" -> Exits the game\n")
    .PrintBar(19)
    .PrintNewLine();
    return *this;
}


CInterface &CInterface::PrintState(const CGameState & state)
{
    PrintMessage("Mode: ");
    state.m_Mode.IsFrenzy() ? PrintMessage("Frenzy\n", EColors::MAGENTA)
                            : PrintMessage("Classic\n");
    PrintMessage("Time: ")
    .PrintMessage(to_string(state.m_Mode.GetTime()))
    .PrintNewLine()
    .PrintMessage("Lives: ")
    .PrintMessage(to_string(state.m_Player->GetLives()), state.m_Player->GetLives() == 1 ? EColors::RED : EColors::GREEN)
    .PrintNewLine()
    .PrintMessage("Score: ")
    .PrintMessage(to_string(state.m_Score) + '/' + to_string(state.GetTargetScore()))
    .PrintNewLine()
    .PrintNewLine();
    return *this;
}

CInterface & CInterface::InitializeBuffer(const CMap & map)
{
    for (auto & i : m_Buffer)
        i.clear();
    m_Buffer.clear();
    m_Buffer.resize(map.GetHeight());
    for (size_t i = 0; i < map.GetHeight(); ++i)
        m_Buffer[i].resize(map.GetWidth());
    return *this;
}

CInterface & CInterface::DrawWalls(const CMap & map)
{
    for (size_t i = 0; i < map.GetHeight(); ++i)
        for (size_t j = 0; j < map.GetWidth(); ++j)
           if(map.IsWall({i,j}))
               m_Buffer[i][j] = '#';
    return *this;
}

CInterface & CInterface::DrawObjects(const CMap & map)
{
    for (size_t i = 0; i < map.GetHeight(); ++i)
        for (size_t j = 0; j < map.GetWidth(); ++j)
            m_Buffer[i][j] = map.GetObjectValue({i,j});
    return *this;
}

CInterface & CInterface::DrawCharacter(const CCharacter & character)
{
    m_Buffer[character.Coord().m_Y][character.Coord().m_X] = character.Value();
    return *this;
}

CInterface & CInterface::FlushBuffer()
{
    for (size_t i = 0; i < m_Buffer.size(); ++i) // NOLINT(modernize-loop-convert)
    {
        for (size_t j = 0; j < m_Buffer[i].size(); ++j)
            PrintChar(m_Buffer[i][j]);
        PrintNewLine();
    }
    PrintNewLine();
    return *this;
}

CInterface & CInterface::PrintChar(const char c)
{
    switch(c)
    {
        case '#': PrepareColor(EColors::BLUE).m_Out << '#'; break;
        case '$': PrepareColor(EColors::MAGENTA).m_Out << '$'; break;
        case '@': PrepareColor(EColors::YELLOW).m_Out << '@'; break;
        case '^': PrepareColor(EColors::YELLOW).m_Out << '^'; break;
        case '>': PrepareColor(EColors::YELLOW).m_Out << '>'; break;
        case '<': PrepareColor(EColors::YELLOW).m_Out << '<'; break;
        case 'v': PrepareColor(EColors::YELLOW).m_Out << 'v'; break;
        case 'A': PrepareColor(EColors::RED).m_Out << 'A'; break;
        case 'B': PrepareColor(EColors::RED).m_Out << 'B'; break;
        case 'X': PrepareColor(EColors::RED).m_Out << 'X'; break;
        case '0': PrepareColor(EColors::GRAY).m_Out << '0'; break;
        case '&': PrepareColor(EColors::CYAN).m_Out << '&'; break;
        default: PrepareColor(EColors::RESET).m_Out << c;
    }
    return *this;
}

CInterface &CInterface::PrepareColor(EColors color)
{
    switch(color)
    {
        case EColors::RESET: m_Out << "\033[0m"; break;
        case EColors::BLUE: m_Out << "\033[1;34m"; break;
        case EColors::GREEN: m_Out << "\033[1;32m"; break;
        case EColors::RED: m_Out << "\033[1;31m"; break;
        case EColors::MAGENTA: m_Out << "\033[1;35m"; break;
        case EColors::YELLOW: m_Out << "\033[1;33m"; break;
        case EColors::GRAY: m_Out << "\033[1;37m"; break;
        case EColors::CYAN: m_Out << "\033[36;1m"; break;
    }
    return *this;
}

CInterface & CInterface::Clear()
{
    system("clear");
    return *this;
}














