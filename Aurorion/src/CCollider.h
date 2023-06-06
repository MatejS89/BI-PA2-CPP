#pragma once

#include "SDL2/SDL_rect.h"

/**
 * @class CCollider
 * @brief Represents a collider object used for collision detection.
 *
 * The CCollider class provides functionality to define and manipulate a rectangular collider.
 * Encapsulates an SDL_Rect object to represent the colliders position and size.
 * Also encapsulates an SDL_Rect representing the buffer of a collider in order to crop the size of the collider.
 */
class CCollider {
public:
    CCollider();

    CCollider(int x, int y, int w, int h);

    ~CCollider();

    const SDL_Rect &GetCollider() const;

    void SetBuffer(int x, int y, int w, int h);

    /**
     * @brief Sets the position and size of the collider.
     * Sets the position and size of the collider's rectangle.
     * @param x The x-coordinate of the collider's top-left corner.
     * @param y The y-coordinate of the collider's top-left corner.
     * @param w The width of the collider.
     * @param h The height of the collider.
     * @note The size of the collider is recalculated based on the set buffer.
     */
    void Set(int x, int y, int w, int h);

private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
};
