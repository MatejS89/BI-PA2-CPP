#include "CPlayer.h"
#include "CInputHandler.h"
#include "CTimer.h"

bool CPlayer::Update() {
    m_currentFrame = (SDL_GetTicks() / 100) % 4;
    HandleInput();
    PlayerCheckCollision();
    IncreaseFallCounter();
    return CEntity::Update();
}

void CPlayer::HandleInput() {
    CEntity::m_RigidBody->UnsetForce();
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_W) &&
        TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_S))
        return;
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_D) &&
        TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_A)) {
        return;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_S))
        CEntity::m_RigidBody->ApplyForceY(MOVEMENT_SPEED * DOWN);

    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_D)) {
        CEntity::m_RigidBody->ApplyForceX(MOVEMENT_SPEED * RIGHT);
        m_Rotation = Rotation::RIGHT;
    }

    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_A)) {
        CEntity::m_RigidBody->ApplyForceX(MOVEMENT_SPEED * LEFT);
        m_Rotation = Rotation::LEFT;
    }

    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_W) && m_IsGrounded) {
        CEntity::m_RigidBody->ApplyForceY(JUMP_FORCE * UP);
        m_IsGrounded = false;
        m_IsJumping = true;
        m_JumpTime = JUMP_TIME;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= TheTimer::Instance().GetDeltaTime();
        m_RigidBody->ApplyForceY(UP * JUMP_FORCE);
    } else {
        m_IsJumping = false;
    }
    if (m_AttackTimer <= 0) {
        if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_SPACE)) {
            TheCollisionHandler::Instance().PlayerAttack(ATTACK_DMG, ATTACK_RANGE, m_Rotation);
            m_AttackTimer = ATTACK_DELAY;
        }
    } else
        m_AttackTimer -= TheTimer::Instance().GetDeltaTime();

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

std::shared_ptr<CGameObject> CPlayer::Create() {
    return std::make_shared<CPlayer>();
}

json CPlayer::Save() const {
    json jsonData;
    SaveEntityData(jsonData);
    jsonData["JUMP_FORCE"] = JUMP_FORCE;
    jsonData["JUMP_TIME"] = JUMP_TIME;
    jsonData["MOVEMENT_SPEED"] = MOVEMENT_SPEED;
    jsonData["ATTACK_DMG"] = ATTACK_DMG;
    jsonData["ATTACK_RANGE"] = ATTACK_RANGE;
    jsonData["ATTACK_DELAY"] = ATTACK_DELAY;
    jsonData["ATTACK_TIMER"] = m_AttackTimer;
    return jsonData;
}

void CPlayer::Load(const json &jsonData) {
    m_Collider.SetBuffer(20, 10, 40, 30);
    CEntity::Load(jsonData);
    m_IsJumping = jsonData["IS_JUMPING"];
    m_IsGrounded = jsonData["IS_GROUNDED"];
    m_FallTime = jsonData["FALL_TIME"];
    m_ImmuneToFall = jsonData["IMMUNE_TO_FALL"];
    m_Rotation = jsonData["ROTATION"];
    JUMP_FORCE = jsonData["JUMP_FORCE"];
    JUMP_TIME = jsonData["JUMP_TIME"];
    MOVEMENT_SPEED = jsonData["MOVEMENT_SPEED"];
    ATTACK_DMG = jsonData["ATTACK_DMG"];
    ATTACK_RANGE = jsonData["ATTACK_RANGE"];
    ATTACK_DELAY = jsonData["ATTACK_DELAY"];
    m_AttackTimer = jsonData["ATTACK_TIMER"];
}

CPlayer::CPlayer() : CEntity() {
    TheTextureManager::Instance().Load
            ("assets/Character/Idle/Idle-Sheet.png", "idle");
}

CPlayer::~CPlayer() = default;
