/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 30.04.2021
 */

#pragma once

#include <cstddef>

/**
 * @brief An enum representing directions
 */
enum class EDirection : size_t
{
    NONE = static_cast<size_t>(-1),
    UP = 0,
    RIGHT = 1,
    LEFT = 2,
    DOWN = 3
};

constexpr const size_t DIRECTIONS = 4;
