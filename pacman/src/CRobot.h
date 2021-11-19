/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 01.05.2021
 */

#pragma once

#include "CCharacter.h"
#include "CMode.h"
#include "CMap.h"
#include "SRandom.h"
#include "CPlayer.h"
#include <memory>

/**
 * @brief An abstract class representing AI - Robots
 */
class CRobot : public CCharacter
{
private:
    static constexpr const size_t DEATH_COUNT = 5;
protected:
    CCoord m_StartingCoords;
    size_t m_DeathCount;

    /**
     * Determines what direction should the robot move in order to
     * get to the target (player) using the shortest way
     *
     * @param[in] target       Coordination of the target (usually player)
     * @param[in] map          Reference to a map where the target is
     * @returns                Most effective direction leading to the target
     * @throws                 std::runtime_error when the target is unreachable
     */
    EDirection BFS(const CCoord & target, const CMap & map) const;

    /**
     * Gets a random direction that does not lead to a wall
     * @param[in] map       Reference to a map (used for checking walls)
     * @returns             Direction not leading to a wall
     */
    EDirection RandomDirection(const CMap & map) const;
public:
    /**
     * A constructor
     * @param[in] val       char graphically representing the robot
     * @param[in] coord     starting coordination of the robot
     */
    CRobot(char val, const CCoord & coord);

    /**
     * Changes the direction of robot, depending on the current mode, player's behaviour and the map
     * Polymorphism is used here - every robot behaves differently
     *
     * @param[in] mode           Reference to the current mode
     * @param[in] player         Reference to the player
     * @param[in] gameMap        Reference to the map
     */
    virtual void ChangeDirection(const CMode & mode, const std::unique_ptr<CPlayer> & player, const CMap & gameMap) = 0;

    /**
     * Reset the robot after it's killed by the player, the robot then waits
     * DEATH_COUNT before it starts moving again.
     */
    void Reset();

    /** TickDeathCount
     * Decrements the death-count of the robot so it can start moving again when it's 0
     */
    void TickDeathCount();
};

