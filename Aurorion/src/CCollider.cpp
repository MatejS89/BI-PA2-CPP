#include "CCollider.h"

CCollider::CCollider(int x, int y, int w, int h) : m_Box({x, y, w, h}), m_Buffer({0, 0, 0, 0}) {
}

const SDL_Rect &CCollider::GetCollider() const {
    return m_Box;
}

void CCollider::SetBuffer(int x, int y, int w, int h) {
    m_Buffer = {x, y, w, h};
}

void CCollider::Set(int x, int y, int w, int h) {
    m_Box = {
            x + m_Buffer.x,
            y + m_Buffer.y,
            w - m_Buffer.w,
            h - m_Buffer.h
    };
}

CCollider::CCollider() = default;
