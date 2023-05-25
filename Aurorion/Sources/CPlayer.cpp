#include "CPlayer.h"
#include "CInputHandler.h"
#include "CCollisionHandler.h"

CPlayer::CPlayer(std::shared_ptr<SParamLoader> params) : CEntity(params) {
    m_Collider.SetBuffer(20, 10, 40, 30);
}

void CPlayer::Draw() {
    CEntity::Draw();
}

void CPlayer::Update(float deltaTime) {
    m_currentFrame = (((SDL_GetTicks() / 100) % 4));
    HandleInput(deltaTime);
    CEntity::Update(deltaTime);
}

void CPlayer::clean() {
}

void CPlayer::HandleInput(float deltatime) {
    TheInputHandler::Instance().Listen();
    CEntity::m_RigidBody->UnsetForce();
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP) &&
        TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_DOWN))
        return;
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_RIGHT) &&
        TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_LEFT)) {
        return;
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_DOWN))
        CEntity::m_RigidBody->ApplyForceY(2 * DOWN);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_RIGHT)) {
        CEntity::m_RigidBody->ApplyForceX(2 * RIGHT);
    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_LEFT)) {
        CEntity::m_RigidBody->ApplyForceX(2 * LEFT);

    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP) && m_IsGrounded) {
        CEntity::m_RigidBody->ApplyForceY(JUMP_FORCE * UP);
        m_IsGrounded = false;
        m_IsJumping = true;
        m_JumpTime = JUMP_TIME;

    }
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP) && m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= deltatime;
        m_RigidBody->ApplyForceY(UP * JUMP_FORCE);
    } else {
        m_IsJumping = false;
    }
//    std::cout << m_JumpTime << std::endl;
}