/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 30.04.2021.
 */

#pragma once

#include "CCoord.h"
#include "EDirection.h"

#include <memory>

/**
 * @brief An abstract class representing any character
 */
class CCharacter
{
protected:
    char m_Value;
    CCoord m_Coord;
    EDirection m_Direction;
public:
    /**
     * A constructor
     * @param[in] value     Char graphically representing the character
     * @param[in] coord     Starting coordination of the character
     */
    CCharacter(char value, const CCoord & coord);
    /**
     * Virtual destructor since the class in abstract
     */
    virtual ~CCharacter() = default;
    CCharacter (const CCharacter & src ) = default;
    CCharacter & operator = (const CCharacter & src) = delete;

    /**
     * Gets the current coordination of the character
     * @returns coordination of the character
     */
    const CCoord & Coord () const;

    /**
     * Sets character's coordination to coord
     * @param[in] coord         Character's new coordination
     */
    void SetCoord (const CCoord & coord);

    /**
     * Gets a char that graphically represents the character
     * @returns value of the character
     */
    char Value() const;

    /**
     * Getter for direction
     * @returns direction of the character
     */
    EDirection Direction() const;
};
