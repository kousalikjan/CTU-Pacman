/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 04.06.2021
 */

#pragma once

#include <cstddef>

/**
 * @brief An enum representing all known characters
 */
enum class ECharacter : size_t
{
    PLAYER = 0,
    ROBOTA = 1,
    ROBOTB = 2,
    ROBOTX = 3
};

constexpr const size_t CHARACTERS = 4;
