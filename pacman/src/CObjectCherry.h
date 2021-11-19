/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 28.05.2021.
 */

#pragma once

#include "CObject.h"

/**
 * @brief A class representing cherries - gamemode changers
 */
class CObjectCherry : public CObject
{
public:
    CObjectCherry();
    std::unique_ptr<CObject> Clone() const override;

    /**
     * Changes the current mode to a new one that's frenzy
     * @returns true
     */
    bool Interact(CGameState & state) const override;
};