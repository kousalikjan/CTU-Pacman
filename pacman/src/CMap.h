/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 30.04.2021.
 */

#pragma once

#include "CObject.h"
#include "CCoord.h"
#include "CGameState.h"
#include "ECharacter.h"

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <set>

/**
 * @brief A class representing map where the game takes place
 */
class CMap
{
private:
    std::string m_FilePath;
    size_t m_Height;
    size_t m_Width;
    size_t m_Gold;
    std::vector<std::vector<bool>> m_Walls;
    std::map<ECharacter, CCoord> m_StartingCoord;
    std::map<CCoord, std::unique_ptr<CObject>> m_Objects;

    /**
     * Determines whether a coordination is valid
     * @param[in] coord     Coordination to be checked
     * @returns TRUE whether coord is valid (inside the map), FALSE otherwise
     */
    bool IsValid(const CCoord & coord) const;

    /**
     * Loads an object from a file
     * @param[in] coord     Coordination of the object
     * @param[in] object    The object
     * @throws ifstream::failure when another is object is at the coord
     */
    void LoadObject (const CCoord & coord, const CObject & object);

    /**
     * Loads walls from the map file, validates them
     * @param[in] input     The input stream with the map file
     * @throws              ifstream::failure when the input is invalid
     */
    void LoadWalls(std::ifstream & input);

    /**
     * Loads cherries from the map file, validates them
     * @param[in] input     The input stream with the map file
     * @throws              ifstream::failure when the input is invalid
     */
    void LoadCherries(std::ifstream & input);

    /**
     * Loads diamonds from the map file, validates them
     * @param[in] input     The input stream with the map file
     * @throws              ifstream::failure when the input is invalid
     */
    void LoadDiamonds(std::ifstream & input);

    /**
     * Loads canals from the map file, validates them
     * @param[in] input     The input stream with the map file
     * @throws              ifstream::failure when the input is invalid
     */
    void LoadCanals(std::ifstream & input);

    /**
     * Loads starting coordinates from the map file, validates them
     * @param[in] input     The input stream with the map file
     * @throws              ifstream::failure when the input is invalid
     */
    void LoadStartingCoord(std::ifstream & input);

    /**
     * Another validation for walls, checks whether there is no space of size 1x1.
     * @throws ifstream::failure when there is a space of size 1x1
     */
    void ValidWalls() const;

    /**
     * Fills all empty spaces with a gold coin (CObjectGold)
     * Increases the target score by one for every gold
     */
    void FillWithGold();

    /**
     * Adds an object to the map when the _coord_ is free
     * @param[in] coord      Coord where the new object should be placed
     * @param[in] object     Reference to the new object
     * @returns TRUE when the object was successfully added, FALSE otherwise
     */
    bool AddObject(const CCoord & coord, const CObject & object);
public:
    /**
     * @param[in] filePath      Path to the map file
     */
    explicit CMap(std::string filePath);

    /**
     * Reads the map file, initializes all walls, objects and gets starting
     * coordination of all characters
     * @throws ifstream::failure when the map file is corrupted or the format is invalid
     */
    void Initialize();

    /**
     * Checks whether the given coordination is a wall
     * @param[in] coord     coordination to be checked
     * @returns TRUE when the coord is a wall, FALSE otherwise
     */
    bool IsWall(const CCoord & coord) const;

    /**
     * Tries to add a cherry, the more free spaces on the map there are,
     * the bigger the chance to add the cherry there is
     */
    void AddCherry();

    /**
     * Calls the Interact method on CObject at the player's coordination.
     * @param[in] state     Reference to the current game-state
     */
    void InteractObjects(CGameState & state);

    /**
     * Gets graphical representation of an object at _coord_
     * @param[in] coord     coord of the object that value is to be returned
     * @returns             value of an object at coord, if there is no object, returns ' '
     */
    char GetObjectValue(const CCoord & coord) const;

    /**
     * Getter for target score
     * @returns the target score
     */
    size_t GetTargetScore() const;

    /**
     * Getter for map height
     * @returns height of the map
     */
    size_t GetHeight() const;

    /**
     * Getter for map width
     * @returns width of the map
     */
    size_t GetWidth() const;

    /**
     * Gets starting coordination of a character
     * @param[in] character    Element from ECharacter enum
     * @returns                Starting coordination of the character
     */
    CCoord GetStartingCoords(ECharacter character) const;
};
