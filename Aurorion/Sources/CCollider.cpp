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

void CCollider::ExtendBuffer(int x) {
    if (x > 0) {
        m_Buffer = {m_Buffer.x,
                    m_Buffer.y,
                    m_Buffer.w + x,
                    m_Buffer.h};
    }
    UpdateBox();
}

void CCollider::UpdateBox() {
    m_Box = {
            m_Box.x + m_Buffer.x,
            m_Box.y + m_Buffer.y,
            m_Box.w - m_Buffer.w,
            m_Box.h - m_Buffer.h
    };
}

void CCollider::ExtendCollider(int x) {
    m_Box =
            {m_Box.x,
             m_Box.y,
             m_Box.w + x,
             m_Box.h
            };
    UpdateBox();
}
