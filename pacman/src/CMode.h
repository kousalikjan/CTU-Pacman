/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 01.05.2021.
 */

#pragma once

#include "CConfig.h"

#include <cstddef>

/**
 * @brief A class representing game mode that affects AI behaviour
 */
class CMode
{
private:
    size_t m_Time;
    EDifficulty m_Difficulty;
    bool m_Bonus;
public:
    /**
     * A constructor
     * @param[in] config    Reference to the current config of the game
     * @param[in] frenzy    Whether the new mode should be bonus(frenzy) or not
     */
    CMode(const CConfig & config, bool frenzy);
    CMode(const CMode & src) = default;
    CMode & operator = (const CMode & src) = default;
    ~CMode() = default;

    /**
     * Gets the time left for current game-mode
     * @returns number of rounds that the current mode will still be active
     */
    size_t GetTime() const;

    /**
     * Decrements the number representing how many round will the current mode still be active
     * @returns reference to *this
     */
    CMode & DecTime();

    /**
     * Getter for difficulty
     * @returns difficulty of the mode
     */
    EDifficulty GetDifficulty() const;

    /**
     * Determines whether the mode is frenzy or not
     * @returns TRUE when the mode is frenzy, FALSE otherwise
     */
    bool IsFrenzy() const;
};

