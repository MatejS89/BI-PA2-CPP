#pragma once

#include "CGameLayer.h"
#include "CGame.h"
#include "CPlayer.h"

class CHudLayer : public CGameLayer {
public:
    void DrawLayer() override;

    void AddTarget();

    void UpdateLayer(float deltaTime) override;

private:
    std::shared_ptr<CPlayer> m_Target;
};
