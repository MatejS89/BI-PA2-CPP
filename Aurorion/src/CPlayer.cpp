#include "CPlayer.h"
#include "CInputHandler.h"
#include "CCollisionHandler.h"
#include "CTimer.h"

CPlayer::CPlayer(const SParamLoader &params) : CEntity(params), m_AttackDelay(0.0F) {
    m_Collider.SetBuffer(20, 10, 40, 30);
    TheTextureManager::Instance().Load
            ("assets/Character/Idle/Idle-Sheet.png", "idle");
    m_CurrHP = MAX_HP;
    m_MaxHP = MAX_HP;
}

void CPlayer::Draw() {
    CEntity::Draw();
}

bool CPlayer::Update() {
    m_currentFrame = (SDL_GetTicks() / 100) % 4;
    HandleInput();
    PlayerCheckCollision();
    IncreaseFallCounter();
    return CEntity::Update();
}

void CPlayer::HandleInput() {
    CEntity::m_RigidBody->UnsetForce();
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP) &&
        TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_DOWN))
        return;
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_RIGHT) &&
        TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_LEFT)) {
        return;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_DOWN))
        CEntity::m_RigidBody->ApplyForceY(MOVEMENT_SPEED * DOWN);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_RIGHT)) {
        CEntity::m_RigidBody->ApplyForceX(MOVEMENT_SPEED * RIGHT);
        m_Rotation = Rotation::RIGHT;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_LEFT)) {
        CEntity::m_RigidBody->ApplyForceX(MOVEMENT_SPEED * LEFT);
        m_Rotation = Rotation::LEFT;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP) && m_IsGrounded) {
        CEntity::m_RigidBody->ApplyForceY(JUMP_FORCE * UP);
        m_IsGrounded = false;
        m_IsJumping = true;
        m_JumpTime = JUMP_TIME;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP) && m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= TheTimer::Instance().GetDeltaTime();
        m_RigidBody->ApplyForceY(UP * JUMP_FORCE);
    } else {
        m_IsJumping = false;
    }
    if (m_AttackDelay <= 0) {
        if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_SPACE)) {
            TheCollisionHandler::Instance().PlayerAttack(ATTACK_DMG, ATTACK_RANGE, m_Rotation);
            m_AttackDelay = ATTACK_DELAY;
        }
    } else
        m_AttackDelay -= TheTimer::Instance().GetDeltaTime();

    if (TheInputHandler::Instance().GetMouseState() == EMouseButtonState::LEFT_BUTTON_DOWN) {
        CCollisionHandler::Instance().DestroyBlock();
    }

    if (TheInputHandler::Instance().GetMouseState() == EMouseButtonState::RIGHT_BUTTON_DOWN) {
        CCollisionHandler::Instance().BuildBlock();
    }
}

void CPlayer::PlayerCheckCollision() {
    UpdateHorizontalMovement();
    UpdateVerticalMovement();
}

void CPlayer::UpdateHorizontalMovement() {
    m_RigidBody->Update();
    m_LastSafePos->SetX(m_Pos->GetX());
    m_Pos->SetX(m_Pos->GetX() + m_RigidBody->GetPosition()->GetX());
    UpdateCollider();
    HandleHorizontalCollisions();
}

void CPlayer::UpdateVerticalMovement() {
    m_RigidBody->Update();
    m_LastSafePos->SetY(m_Pos->GetY());
    m_Pos->SetY(m_Pos->GetY() + m_RigidBody->GetPosition()->GetY());
    UpdateCollider();
    HandleVerticalCollisions();
}

void CPlayer::HandleHorizontalCollisions() {
    if (m_Collider.GetCollider().x < 0 ||
        m_Collider.GetCollider().x + m_Collider.GetCollider().w > TheGame::Instance().GetMapWidth() ||
        CCollisionHandler::Instance().MapCollision(m_Collider.GetCollider(), m_CurrHP) ||
        CCollisionHandler::Instance().CheckCollisionWithEnemies()) {
        m_Pos->SetX(m_LastSafePos->GetX());
    }
}

void CPlayer::HandleVerticalCollisions() {
    if (CCollisionHandler::Instance().MapCollision(m_Collider.GetCollider(), m_CurrHP) ||
        CCollisionHandler::Instance().CheckCollisionWithEnemies()) {
        m_IsGrounded = true;
        DealFallDamage();
        m_ImmuneToFall = false;
        m_FallTime = 0.0F;
        m_Pos->SetY(m_LastSafePos->GetY());
    } else {
        IncreaseFallCounter();
        m_IsGrounded = false;
    }
}

std::shared_ptr<CGameObject> CPlayer::Create(const SParamLoader &params) {
    return std::make_shared<CPlayer>(params);
}

void CPlayer::Save() const {
    WriteToJson(ConvertToJson(), "player.json");
}

json CPlayer::ConvertToJson() const {
    json jsonData;
    jsonData["JUMP_FORCE"] = JUMP_FORCE;
    jsonData["JUMP_TIME"] = JUMP_TIME;
    jsonData["MOVEMENT_SPEED"] = MOVEMENT_SPEED;
    jsonData["MAX_HP"] = MAX_HP;
    jsonData["ATTACK_DMG"] = ATTACK_DMG;
    jsonData["ATTACK_RANGE"] = ATTACK_RANGE;
    jsonData["ATTACK_DELAY"] = ATTACK_DELAY;
    return jsonData;
}

void CPlayer::WriteToJson(const json &jsonData, const std::string &filePath) const {
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << jsonData.dump(4);  // Indentation of 4 spaces
        file.close();
        std::cout << "JSON data saved to " << filePath << std::endl;
    } else {
        std::cout << "Failed to open file: " << filePath << std::endl;
    }
}

CPlayer::~CPlayer() = default;