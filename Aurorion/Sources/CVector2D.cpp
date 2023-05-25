#include <cmath>
#include "CVector2D.h"

CVector2D::CVector2D() : m_X(0), m_Y(0) {}

CVector2D::CVector2D(int x, int y) : m_X(x), m_Y(y) {}

int CVector2D::GetX() const {
    return m_X;
}

int CVector2D::GetY() const {
    return m_Y;
}

void CVector2D::SetX(int x) {
    m_X = x;
}

void CVector2D::SetY(int y) {
    m_Y = y;
}

double CVector2D::length() const {
    return hypot(m_X, m_Y);
}

CVector2D CVector2D::operator+(const CVector2D &other) const {
    return CVector2D(m_X + other.m_X, m_Y + other.m_Y);
}

CVector2D &CVector2D::operator+=(CVector2D &other) {
    m_X += other.m_X;
    m_Y += other.m_Y;
    return *this;
}

CVector2D CVector2D::operator*(int scalar) {
    return CVector2D(m_X * scalar, m_Y * scalar);
}

CVector2D &CVector2D::operator*=(int scalar) {
    m_X *= scalar;
    m_Y *= scalar;
    return *this;
}

CVector2D CVector2D::operator-(const CVector2D &other) const {
    return CVector2D(m_X - other.m_X, m_Y - other.m_Y);
}

CVector2D &CVector2D::operator-=(const CVector2D &other) {
    m_X -= other.m_X;
    m_Y -= other.m_Y;
    return *this;
}

CVector2D CVector2D::operator/(const CVector2D &other) const {
    return CVector2D(m_X / other.m_X, m_Y / other.m_Y);
}

CVector2D &CVector2D::operator/=(int scalar) {
    m_X /= scalar;
    m_Y /= scalar;
    return *this;
}

void CVector2D::normalize() {
    float len = length();
    if (len > 0)
        *this *= 1 / len;
}