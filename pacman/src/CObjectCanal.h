/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 28.05.2021.
 */

#pragma once

#include "CObject.h"
#include "CCoord.h"

/**
 * @brief A class representing canal
 */
class CObjectCanal: public CObject
{
private:
    CCoord m_Destination;
public:
    /**
     * A constructor
     * @param[in] coord     The other end of the canal
     */
    explicit CObjectCanal(const CCoord & coord);

    std::unique_ptr<CObject> Clone() const override;

    /**
     * Sets player's coordination to the other canal at the map
     * @returns false
     */
    bool Interact(CGameState & state) const override;

};