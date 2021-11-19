/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 30.04.2021
 */

#pragma once

#include "EDirection.h"

#include <cstddef>

/**
 * @brief A struct representing coordination
 */
struct CCoord
{
    size_t m_Y;
    size_t m_X;
    /**
     * Default constructor
     * The game uses [Y][X] format and behaves like a matrix,
     * so the most upper left field has coordination [0][0]
     * Initializes coord to [0][0] value
     */
    CCoord();

    /**
     * A constructor
     * @param y     distance from 0 at Y axis
     * @param x     distance from 0 at X axis
     */
    CCoord(size_t y, size_t x);
    /**
     * Checks for equality
     * @param rhs   other coordination
     * @return      TRUE when coords are equal
     */
    bool operator == (const CCoord & rhs) const;
    /**
     * Checks for inequality
     * @param rhs   other coordination
     * @return      TRUE when coords are not equal
     */
    bool operator != (const CCoord & rhs) const;
    bool operator < (const CCoord & rhs) const;
    /**
     * Add coord and direction
     * @param direction to be added
     * @return new CCoord that is the original plus the direction
     */
    CCoord operator + (const EDirection & direction) const;
};

