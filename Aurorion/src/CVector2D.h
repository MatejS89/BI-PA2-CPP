#pragma once

class CVector2D {
public:
    CVector2D();

    CVector2D(int x, int y);

    int GetX() const;

    int GetY() const;

    void SetX(int x);

    void SetY(int y);

    double length() const;

    CVector2D operator+(const CVector2D &other) const;

    CVector2D &operator+=(CVector2D &other);

    CVector2D operator*(int scalar);

    CVector2D &operator*=(int scalar);

    CVector2D operator-(const CVector2D &other) const;

    CVector2D &operator-=(const CVector2D &other);

    CVector2D operator/(const CVector2D &other) const;

    CVector2D &operator/=(int scalar);

    // Creates a normalized vector ( unit vector ) which is used to describe the direction
    void normalize();

private:
    int m_X;
    int m_Y;
};