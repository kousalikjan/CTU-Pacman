/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 30.04.2021.
 */

#pragma once

#include "CMap.h"
#include "CInterface.h"
#include "CCoord.h"
#include "CRobot.h"
#include "CGameState.h"

#include <memory>
#include <vector>

/**
 * @brief A class representing the actual game
 */
class CGame
{
private:
    CMap m_Map;
    CGameState m_State;
    std::shared_ptr<CInterface> m_Interface;
    std::vector<std::unique_ptr<CRobot>> m_Robots;
    bool m_Active;
    bool m_Win;

    /**
     * Moves a character in its direction
     * @param[in] character     Character to be moved
     */
    void MoveCharacter(CCharacter & character) const;

    /**
     * Prompts for a direction and then moves the player
     * @returns FALSE if the player exits the game, TRUE otherwise
     */
    bool MovePlayer();

    /**
     * Checks whether player collided with a robot
     * @returns TRUE when the player dies from the collision, FALSE otherwise
     */
    bool CheckCollisions();

    /**
     * Interacts with an object at the player's coordination
     */
    void CheckObjects();

    /**
     * Changes direction of all robots and moves them
     */
    void MoveRobots() const;

    /**
     * Checks whether the mode should be changed, changes it if so
     */
    void CheckMode();

    /**
     * Adds a cherry depending on the config file
     */
    void AddCherry();

    /**
     * Checks whether the game was won
     * @returns TRUE if the game was won, FALSE otherwise
     */
    bool GameWin();

    /**
     * Decrements every robot's death count
     */
    void TickDeathCount();

    /**
     * Redraws the whole interface
     */
    void RedrawInterface () const;

public:
    /**
     * A constructor
     * param[in] map            Initialized map to be played
     * param[in] state          Initialized game-state
     * param[in] interface      Reference to the interface of the application
     */
    CGame(CMap map, CGameState state, const std::shared_ptr<CInterface> & interface);

    /**
     * Starts and runs the game
     */
    void Run ();

    /**
     * Ends the game, prints win/defeat announcement
     */
    void End() const;
};
