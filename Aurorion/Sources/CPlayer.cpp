#include "CPlayer.h"
#include "CInputHandler.h"
#include "CCollisionHandler.h"
#include "CTimer.h"

CPlayer::CPlayer(std::shared_ptr<SParamLoader> params) : CEntity(params) {
    m_Collider.SetBuffer(20, 10, 40, 30);
    TheTextureManager::Instance().Load
            ("assets/Character/Idle/Idle-Sheet.png", "idle");
    m_CurrHP = MAX_HP;
    m_MaxHP = MAX_HP;
}

void CPlayer::Draw() {
    CEntity::Draw();
}

bool CPlayer::Update(float deltaTime) {
    m_currentFrame = (((SDL_GetTicks() / 100) % 4));
    HandleInput(deltaTime);
    return CEntity::Update(deltaTime);
    if (m_RigidBody->GetVelocity().GetY() > 0 && !m_IsGrounded)
        std::cout << "FALLING" << std::endl;
    else
        std::cout << "NOT FALLING" << std::endl;
}

void CPlayer::clean() {
}

void CPlayer::HandleInput(float deltaTime) {
    CEntity::m_RigidBody->UnsetForce();
//    std::cout << deltaTime << "     " << TheTimer::Instance().GetDeltaTime() << std::endl;
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
        m_Flip = SDL_FLIP_NONE;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_LEFT)) {
        CEntity::m_RigidBody->ApplyForceX(MOVEMENT_SPEED * LEFT);
        m_Flip = SDL_FLIP_HORIZONTAL;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP) && m_IsGrounded) {
        CEntity::m_RigidBody->ApplyForceY(JUMP_FORCE * UP);
        m_IsGrounded = false;
        m_IsJumping = true;
        m_JumpTime = JUMP_TIME;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP) && m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= deltaTime;
        m_RigidBody->ApplyForceY(UP * JUMP_FORCE);
    } else {
        m_IsJumping = false;
    }

    if (TheInputHandler::Instance().GetMouseState() == EMouseButtonState::LEFT_BUTTON_DOWN) {
        CCollisionHandler::Instance().DestroyBlock();
    }

    if (TheInputHandler::Instance().GetMouseState() == EMouseButtonState::RIGHT_BUTTON_DOWN) {
        CCollisionHandler::Instance().BuildBlock();
    }

    
}