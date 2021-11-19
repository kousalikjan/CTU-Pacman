/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 02.06.2021
 */

#pragma once

#include <exception>

/**
 * @brief custom general exception
 */
struct game_exit : public std::exception {};