/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 28.05.2021.
 */

#pragma once

#include "CPlayer.h"
#include "CMode.h"
#include "CConfig.h"
#include "CCoord.h"
#include <memory>
#include <cstddef>

/**
 *  @brief A class representing current state of the game,
 *  it wraps CPlayer, CConfig, CMode and the current score together.
 *  The class was added as a wrapper for polymorphism by CObject
 */
class CGameState
{
private:
    size_t m_TargetScore;
public:
    std::unique_ptr<CPlayer> m_Player;
    CConfig m_Config;
    CMode m_Mode;
    size_t m_Score;

    /**
     * A constructor
     * @param[in] playerCoord       Starting coordination of player
     * @param[in] config            Initialized config of the game
     * @param[in] targetScore       Points to gather in order to win
     */
    CGameState(const CCoord & playerCoord, CConfig config, size_t targetScore);

    /**
     * Getter for target score
     * @returns the target score
     */
    size_t GetTargetScore() const;
};
