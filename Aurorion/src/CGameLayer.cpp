#include "CGameLayer.h"

std::shared_ptr<CMap> CGameLayer::GetMap() {
    return nullptr;
}

json CGameLayer::LoadJsonFromFile(const std::string &filePath) const {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    json jsonData;
    file >> jsonData;
    file.close();
    return jsonData;
}