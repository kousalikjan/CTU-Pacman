//
// @author Jan Kousalík <kousaja1@fit.cvut.cz>
// @date 01.05.2021.
//

#pragma once

#include <memory>

#include "CRobot.h"

/**
 * @brief A class representing AI of type A
 */
class CRobotA : public CRobot
{
public:
    /**
     * A constructor
     * @param coord     Starting coordination
     */
    explicit CRobotA(const CCoord & coord);

    /**
     * Changes direction of the robot following those rules:
     * Mode: FRENZY or EASY - Random direction
     * Mode: HARD -           BFS
     * @param[in] mode           Reference to the current mode
     * @param[in] player         Reference to the player
     * @param[in] gameMap        Reference to the map
     */
    void ChangeDirection(const CMode & mode, const std::unique_ptr<CPlayer> & player, const CMap & gameMap) override;
};
