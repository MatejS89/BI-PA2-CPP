#pragma once

class CMapLayer {
public:
    virtual void LayerRender() = 0;

    virtual void LayerUpdate() = 0;
};
