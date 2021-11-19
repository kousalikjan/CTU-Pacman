/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 31.05.2021
 */

#pragma once

#include "EDirection.h"
#include "CCoord.h"

#include <cstddef>

/**
 * @brief
 * Struct used for generating random stuff
 */
struct SRandom
{
    /**
     * The constructor is deleted since the struct is static
     */
    SRandom() = delete;

    /**
     * Initializes the class, must be called before any further usage
     */
    static void Initialize();

    /**
     * Generates a random index
     * @param[in] limit    The smallest number that won't be generated
     * @return             Random number from 0 (included) to _limit_ (except)
     */
    static size_t RandomIdx(size_t limit = -1);

    /**
     * Generates a random coordination
     * @param[in] height   The smallest number on Y axis that won't be generated
     * @param[in] width    The smallest number on X axis that won't be generated
     * @returns            Coordination with random Y and X value within the given limits
     */
    static CCoord RandomCoord(size_t height, size_t width);

    /**
     * Generates a random direction
     * @returns           random direction except EDirection::NONE
     */
    static EDirection RandomDireciton();
};
