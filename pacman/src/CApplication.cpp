//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 08.05.2021.
//


#include "CApplication.h"
#include "ECharacter.h"

#include <fstream>

using namespace std;

CApplication::CApplication(shared_ptr<CInterface> interface) : m_Interface(move(interface)), m_Active(true) {}

bool CApplication::Run()
{
    PrintMenu();
    while(m_Active)
    {
        try {
            switch (GetCommand()) {
                case ECommand::ERROR:
                    m_Interface->PrintMessage("\033[1;31mUnknown command!\033[0m\n");
                    break;
                case ECommand::NEW:
                    m_Interface->Clear();
                    if (!InitializeGame()) break;
                    try { m_Game->Run(); }
                    catch(const runtime_error & e)
                    {
                        m_Interface->Clear()
                        .PrintMessage("An error while playing the game!\n")
                        .PrintMessage(e.what())
                        .PrintNewLine()
                        .PrintMainMenu();
                        break;
                    }
                    m_Game->End();
                    break;
                case ECommand::HELP:
                    PrintHelp();
                    break;
                case ECommand::QUIT:
                    m_Interface->Clear();
                    m_Active = false;
                    return false;
            }
        }
        catch (const ios_base::failure & e)
        {
            m_Interface->Clear();
            m_Active = false;
            return true;
        }
    }
    return false;
}

bool CApplication::InitializeGame()
{
    CMap map(move( m_Interface->PromptMapFilename()));
    m_Interface->PrintNewLine();
    CConfig config(move(m_Interface->PromptConfigFilename()));
    try {
        config.Initialize();
        map.Initialize();
    }
    catch (const ifstream::failure & e) {
        m_Interface->Clear()
        .PrintMessage("An error occurred while reading game-files!\n")
        .PrintMessage(e.what())
        .PrintNewLine()
        .PrintMainMenu();
        return false;
    }
    CGameState state(map.GetStartingCoords(ECharacter::PLAYER), move(config), map.GetTargetScore());
    m_Game = make_unique<CGame>(CGame(move(map), move(state), m_Interface));
    return true;
}

void CApplication::PrintMenu() const
{
    m_Interface->Clear()
    .PrintMainMenu();
}

void CApplication::PrintHelp() const
{
    m_Interface->Clear()
            .PrintMenuHelp();
}

ECommand CApplication::GetCommand() const
{
    return m_Interface->PromptCommand();
}
