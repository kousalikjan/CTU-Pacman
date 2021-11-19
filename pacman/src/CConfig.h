/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 05.05.2021
 */

#pragma once

#include "EDifficulty.h"

#include <cstddef>
#include <string>

/**
 * @brief A class representing the current configuration of a game
 * Holds together information of the durations of each CMode, what's the EDifficulty
 * and what's the probability of adding a CObjectCherry
 */
class CConfig
{
private:
    std::string m_FilePath;
    size_t m_NormalTime;
    size_t m_FrenzyTime;
    EDifficulty m_Difficulty;
    size_t m_Probability;
public:
    /**
     * A constructor
     * @param[in] filepath      Path to the config file
     * */
    explicit CConfig(std::string filepath);

    /**
     * Reads the config file, initializes all values
     * */
    void Initialize();

    /**
     * Gets for how many rounds will the classic mode be active (if cherry is not picked up)
     * @returns number of rounds of the classic game-mode
     * */
    size_t GetNormalTime() const;

    /**
     * Gets for how many round will the frenzy mode be active
     * @returns number of rounds of the frenzy game-mode
     * */
    size_t GetFrenzyTime() const;

    /**
     * Getter for difficulty
     * @returns difficulty of the current config
     * */
    EDifficulty GetDifficulty() const;

    /**
     * Getter for probability
     * @returns probability of adding a cherry every round
     * */
    size_t GetProbability() const;
};
