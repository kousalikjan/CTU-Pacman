/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 05.05.2021
 */

#pragma once

#include <cstddef>

/**
 * @brief An enum representing all known commands
 */
enum class ECommand : size_t
{
    ERROR = 0,
    NEW = 1,
    HELP = 2,
    QUIT = 3
};
