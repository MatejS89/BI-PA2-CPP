#pragma once

#include "CGameLayer.h"
#include "CGame.h"
#include "CGameObject.h"

class CHudLayer : public CGameLayer {
public:
    void DrawLayer() override;

    void AddTarget(std::shared_ptr<CGameObject> target);

    void UpdateLayer() override;

    void SaveLayer() override;

private:
    std::shared_ptr<CGameObject> m_Target;
};
