/**
 * @author Jan Kousalík <kousaja1@fit.cvut.cz>
 * @date 28.05.2021.
 */

#pragma once

#include "CGameState.h"

#include <memory>

/**
 * @brief An abstract class representing an object that player can interact with
 */
class CObject
{
private:
    char m_Value;
public:
    /**
     * A constructor
     * @param[in] value     char graphically representing the object
     */
    explicit CObject(char value);

    /**
     * Virtual destructor since the class in abstract
     */
    virtual ~CObject() = default;
    CObject(const CObject & src) = default;
    CObject & operator = (const CObject & src) = delete;

    /**
     * Getter for value that graphically represents the object
     * @returns value of the object
     */
    char Value() const;

    /**
     * Virtual method that clones the object
     * @returns std:unique_ptr of the current instance
     */
    virtual std::unique_ptr<CObject> Clone () const = 0;

    /**
     * Changes the current game's game-state
     * Polymorphism is used here - every block changes the game-state differently
     * @param[in] state         Reference to the current game-state
     * @returns TRUE whether the object is to be deleted from game, FALSE otherwise
     */
    virtual bool Interact(CGameState & state) const = 0;

};
