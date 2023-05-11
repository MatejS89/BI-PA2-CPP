#pragma once

class CVector2D {
public:
    CVector2D();

    CVector2D(float x, float y);

    float GetX() const;

    float GetY() const;

    void SetX(float x);

    void SetY(float y);

    float length() const;

    CVector2D operator+(const CVector2D &other) const;

    CVector2D &operator+=(CVector2D &other);

    CVector2D operator*(float scalar);

    CVector2D &operator*=(float scalar);

    CVector2D operator-(const CVector2D &other) const;

    CVector2D &operator-=(const CVector2D &other);

    CVector2D operator/(const CVector2D &other) const;

    CVector2D &operator/=(float scalar);

    // Creates a normalized vector ( unit vector ) which is used to describe the direction
    void normalize();

private:
    float m_X;
    float m_Y;
};