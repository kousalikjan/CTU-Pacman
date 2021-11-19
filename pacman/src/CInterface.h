/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 30.04.2021
 */

#pragma once

#include "EDirection.h"
#include "CMap.h"
#include "ECommand.h"
#include "CCharacter.h"
#include "CGameState.h"
#include "EColors.h"

#include <cstddef>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

/**
 * @brief A class that is used to communicate with the user
 */
class CInterface
{
private:
    std::istream & m_In;
    std::ostream & m_Out;
    std::string m_MapNames[11] = {"./examples/maps/city.txt",
                                  "./examples/maps/metro.txt",
                                  "./examples/maps/space.txt",
                                  "./examples/maps/corrupted/2bots.txt",
                                  "./examples/maps/corrupted/badwalls.txt",
                                  "./examples/maps/corrupted/nocanal.txt",
                                  "./examples/maps/corrupted/nodiamond.txt",
                                  "./examples/maps/corrupted/playerinwall.txt",
                                  "./examples/maps/corrupted/wrongheight.txt",
                                  "./examples/maps/corrupted/wrongrow.txt",
                                  "./examples/maps/corrupted/unreachable.txt"};
    static constexpr const size_t MAP_INDEXES = 10;
    std::string m_ConfigNames[6] = {"./examples/configs/easy.txt",
                                    "./examples/configs/hard.txt",
                                    "./examples/configs/corrupted/101probability.txt",
                                    "./examples/configs/corrupted/missing.txt",
                                    "./examples/configs/corrupted/negative.txt",
                                    "./examples/configs/corrupted/nochar.txt"};
    static constexpr const size_t CONFIG_INDEXES = 5;
    std::vector<std::vector<char>> m_Buffer;

    /**
     * Asks user to enter index until an index in range from 0 to max is given
     * @param[in] max               The highest index that will be accepted
     * @returns                     An index given by the user
     * @throws ios_base::failure    when EOF is detected
     */
    size_t PromptIndex(int max);

    /**
     * Prints help when a wrong input during prompting direction is given
     * @returns *this
     */
    CInterface & PrintDirectionHelp();

    /**
     * Sends an ANSI code to the output representing the color given
     * @param[in] color     Color to be prepared
     * @returns *this
     */
    CInterface & PrepareColor(EColors color);

    /**
     * Prints a bar (-----) of the given length and color
     * @param[in] length     Length of the bar
     * @param[in] color      Color of the bar
     * @returns *this
     */
    CInterface & PrintBar(size_t length = 32, EColors color = EColors::YELLOW);

    /**
     * Prints a char, specific characters are printed in a color
     * @param[in] c      Char to be printed
     * @returns          *this
     */
    CInterface & PrintChar(char c);

public:
    /**
     * A constructor
     * @param[in] in      Input stream
     * @param[in] out     Output stream
     */
    CInterface( std::istream & in, std::ostream & out);

    /**
     * Prints a message in a color given
     * @param[in] message       Message to be printed
     * @param[in] color         Color of the message
     * @returns                 *this
     */
    CInterface & PrintMessage(const std::string & message, EColors color = EColors::RESET);

    /**
     * Prints the main menu
     * @returns *this;
     */
    CInterface & PrintMainMenu();

    /**
     * Print help when wrong command is given in the main menu
     * @returns *this
     */
    CInterface & PrintMenuHelp();

    /**
     * Prints a new line
     * @return *this
     */
    CInterface & PrintNewLine();

    /**
     * Prints announcement that the game was won
     * @returns *this
     */
    CInterface & PrintWin();

    /**
     * Prints announcement that the game was lost
     * Also prints player's score and the target score
     * @param[in] state     The current game-state
     * @returns             *this
     */
    CInterface & PrintDefeat(const CGameState & state);

    /**
     * Prompts for an index of map
     * @returns path to the file of the map selected
     */
    std::string PromptMapFilename ();

    /**
    * Prompts for an index of config
    * @returns path to the file of the config selected
    */
    std::string PromptConfigFilename();

    /**
     * Prompts for a direction
     * @returns returns the direction selected
     * @throws game_exit when the user decides to exit the game
     */
    EDirection PromptDirection();

    /**
     * Prompts for a command, calls PrintMenuHelp when an unknown command is given
     * @returns the command selected
     */
    ECommand PromptCommand();

    /**
     * Clears the console
     * @returns *this
     */
    CInterface & Clear ();

    /**
     * Flushes the buffer to the output
     * @returns *this
     */
    CInterface & FlushBuffer ();

    /**
     * Clears old buffer, sets up a new one with size according to the map
     * @param[in] map      Current map
     * @returns            *this
     */
    CInterface & InitializeBuffer(const CMap & map);

    /**
     * Print game-state (mode, score, lives, time until new mode)
     * @param[in] state       State to be printed
     * @returns               *this
     */
    CInterface & PrintState (const CGameState & state);

    /**
     * Draws all objects from a map into a buffer
     * @param[in] map       Map containing the objects
     * @returns             *this
     */
    CInterface & DrawObjects(const CMap & map);

    /**
     * Draws a character into a buffer
     * @param[in] character     Character to be drawn
     * @returns                 *this
     */
    CInterface & DrawCharacter(const CCharacter & character);

    /**
     * Draws all walls from a map into a buffer
     * @param[in] map       Map containing the walls
     * @returns             *this
     */
    CInterface & DrawWalls(const CMap & map);
};
