#include "Player.hpp"

#include <vector>

#include "../physics/World.hpp"

Player::Player(b2Body* body) : Body(body) {
    type = BodyType::PLAYER;
    m_healthPoints = 100;
    m_pInputDevice = new InputDevice();
    m_maxJumpCount = 2;
    m_jumpCount = m_maxJumpCount;
    m_jumpRecoveryTime = 0;
}

Player::~Player() { delete m_pInputDevice; }

void Player::update() {
    Body::update();

    if (m_jumpRecoveryTime > 0) {
        m_jumpRecoveryTime--;
    }

    std::vector<InputAction> actions = m_pInputDevice->getActions();

    b2Vec2 moveVector;
    moveVector.x = 0.0f;
    moveVector.y = m_pBody->GetLinearVelocity().y;

    for (InputAction action : actions) {
        if (action == InputAction::RIGHT) {
            moveVector.x = 15.0f;
        } else if (action == InputAction::LEFT) {
            moveVector.x = -15.0f;
        } else if (action == InputAction::JUMP && m_jumpCount > 0 && m_jumpRecoveryTime == 0) {
            moveVector.y = 30.0f;
            m_jumpCount--;
            m_jumpRecoveryTime = World::FPS / 2;
        }
    }

    m_pBody->SetLinearVelocity(moveVector);
}

void Player::resetJumpCount() {
    m_jumpCount = m_maxJumpCount;
    m_jumpRecoveryTime = 0;
}