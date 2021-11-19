/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 05.05.2021.
 */

#pragma once

#include "CInterface.h"
#include "CGame.h"
#include "ECommand.h"

#include <memory>

/**
 * @brief A class that holds the whole application together
 */
class CApplication
{
private:
    std::shared_ptr<CInterface> m_Interface;
    std::unique_ptr<CGame> m_Game = nullptr;
    bool m_Active;
    /**
     * Prints the main menu
     */
    void PrintMenu() const;

    /**
     * Prints the menu help
     */
    void PrintHelp() const;

    /**
     * Prompts user for a command
     */
    ECommand GetCommand() const;

    /**
     * Initializes game, loading all necessary variables from game-files
     * @returns TRUE if initializes correctly, FALSE otherwise
     */
    bool InitializeGame();
public:
    /**
     * A constructor
     * @param[in] interface     Reference to the current interface
     */
    explicit CApplication(std::shared_ptr<CInterface> interface);

    /**
     * Runs the application
     * @returns FALSE whether the application ended correctly (using command quit), TRUE otherwise
     */
    bool Run();
};

