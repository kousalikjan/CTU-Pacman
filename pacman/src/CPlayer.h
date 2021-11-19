/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 01.05.2021
 */

#pragma once

#include "CCharacter.h"

#include <memory>
#include <cstddef>

/**
 * @brief A class representing the user/player
 */
class CPlayer : public CCharacter
{
private:
    char NewValue();
    size_t m_Lives;
public:
    /**
     * A constructor
     * @param[in] coord     Starting coordination of the player
     */
    explicit CPlayer(const CCoord & coord);

    /**
     * Sets new direction of the player
     * @param[in] direction      New direction
     */
    void SetDirection (const EDirection & direction);

    /**
     * Decrements player's lives if the mode is classic
     * @param[in] frenzy         true when the mode is frenzy, false otherwise
     */
    void Collision(bool frenzy);

    /**
     * Checks whether the player is dead
     * @returns TRUE when the player is dead, FALSE otherwise
     */
    bool IsDead() const;

    /**
     * Getter for player's lives
     * @returns amount of player's lives
     */
    size_t GetLives() const;
};
