/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 28.05.2021
 */

#pragma once

#include "CObject.h"

/**
 * @brief A class representing gold
 */
class CObjectGold : public CObject
{
public:
    CObjectGold();
    std::unique_ptr<CObject> Clone() const override;

    /**
     * Increments score by one point
     * @returns true
     */
    bool Interact(CGameState & state) const override;
};
