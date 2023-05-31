#include "CPlayer.h"

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
    jsonData["WIDTH"] = m_W;
    jsonData["HEIGHT"] = m_H;
    jsonData["CURRENT_ROW"] = m_currentRow;
    jsonData["CURRENT_FRAME"] = m_currentFrame;
    jsonData["TEXTURE"] = m_texture;
    jsonData["POS_X"] = m_Pos->GetX();
    jsonData["POS_Y"] = m_Pos->GetY();
    jsonData["LAST_SAFE_POSX"] = m_LastSafePos->GetX();
    jsonData["LAST_SAFE_POSY"] = m_LastSafePos->GetY();
    m_RigidBody->SetPosition(*m_Pos);
    jsonData["IS_JUMPING"] = m_IsJumping;
    jsonData["IS_GROUNDED"] = m_IsGrounded;
    jsonData["FALL_TIME"] = m_FallTime;
    jsonData["IMMUNE_TO_FALL"] = m_ImmuneToFall;
    jsonData["ROTATION"] = m_Rotation;
    jsonData["JUMP_FORCE"] = JUMP_FORCE;
    jsonData["JUMP_TIME"] = JUMP_TIME;
    jsonData["MOVEMENT_SPEED"] = MOVEMENT_SPEED;
    jsonData["CURR_HP"] = m_CurrHP;
    jsonData["MAX_HP"] = m_MaxHP;
    jsonData["ATTACK_DMG"] = ATTACK_DMG;
    jsonData["ATTACK_RANGE"] = ATTACK_RANGE;
    jsonData["ATTACK_DELAY"] = ATTACK_DELAY;
    jsonData["ATTACK_TIMER"] = m_AttackTimer;
    m_Centre->SetX(m_Pos->GetX() + m_W / 2);
    m_Centre->SetY(m_Pos->GetY() + m_H / 2);
    return jsonData;
}

void CPlayer::Load(const json &jsonData) {
    m_W = jsonData["WIDTH"];
    m_H = jsonData["HEIGHT"];
    m_currentRow = jsonData["CURRENT_ROW"];
    m_currentFrame = jsonData["CURRENT_FRAME"];
    m_texture = jsonData["TEXTURE"];
    m_Pos->SetX(jsonData["POS_X"]);
    m_Pos->SetY(jsonData["POS_Y"]);
    m_LastSafePos->SetX(jsonData["LAST_SAFE_POSX"]);
    m_LastSafePos->SetY(jsonData["LAST_SAFE_POSY"]);
    m_IsJumping = jsonData["IS_JUMPING"];
    m_IsGrounded = jsonData["IS_GROUNDED"];
    m_FallTime = jsonData["FALL_TIME"];
    m_ImmuneToFall = jsonData["IMMUNE_TO_FALL"];
    m_Rotation = jsonData["ROTATION"];
    JUMP_FORCE = jsonData["JUMP_FORCE"];
    JUMP_TIME = jsonData["JUMP_TIME"];
    MOVEMENT_SPEED = jsonData["MOVEMENT_SPEED"];
    m_CurrHP = jsonData["CURR_HP"];
    m_MaxHP = jsonData["MAX_HP"];
    ATTACK_DMG = jsonData["ATTACK_DMG"];
    ATTACK_RANGE = jsonData["ATTACK_RANGE"];
    ATTACK_DELAY = jsonData["ATTACK_DELAY"];
    m_AttackTimer = jsonData["ATTACK_TIMER"];
    m_Collider.SetBuffer(20, 10, 40, 30);
    m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W, m_H);
}

CPlayer::CPlayer() : CEntity() {
    TheTextureManager::Instance().Load
            ("assets/Character/Idle/Idle-Sheet.png", "idle");
}

CPlayer::~CPlayer() = default;
