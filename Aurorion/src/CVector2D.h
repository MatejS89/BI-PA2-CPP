#pragma once

/** @class CVector2D
* @brief The CVector2D class represents a 2D vector.
* The CVector2D class provides functionality for working with 2D vectors,
* including basic arithmetic operations and length calculation.
*/
class CVector2D {
public:
    CVector2D();

    CVector2D(int x, int y);

    int GetX() const;

    int GetY() const;

    void SetX(int x);

    void SetY(int y);

    CVector2D operator+(const CVector2D &other) const;

    CVector2D &operator+=(CVector2D &other);

    CVector2D operator*(int scalar);

    CVector2D &operator*=(int scalar);

    CVector2D operator-(const CVector2D &other) const;

    CVector2D &operator-=(const CVector2D &other);

    CVector2D operator/(const CVector2D &other) const;

    CVector2D &operator/=(int scalar);

private:
    int m_X;
    int m_Y;
};