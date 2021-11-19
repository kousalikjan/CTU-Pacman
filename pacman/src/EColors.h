/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 02.06.2021
 */

#pragma once

#include <cstddef>

/**
 * @brief An enum representing all known colors
 */
enum class EColors : size_t
{
    RESET = 0,
    BLUE = 1,
    GREEN = 2,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    GRAY = 7,
    CYAN = 8
};
