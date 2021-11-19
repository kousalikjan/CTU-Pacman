/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 02.06.2021
 */

#pragma once

#include "CObject.h"

/**
 * @brief A class representing diamond
 */
class CObjectDiamond : public CObject
{
public:
    static constexpr const size_t DIAMOND_VALUE = 15;
    CObjectDiamond();
    std::unique_ptr<CObject> Clone() const override;

    /**
     * Increments score by DIAMOND_VALUE
     * @returns true
     */
    bool Interact(CGameState & state) const override;
};
