#include "Player.hpp"

#include <vector>

Player::Player(b2Body* body) : Body(body) {
    type = BodyType::PLAYER;
    m_healthPoints = 100;
    m_pInputDevice = new InputDevice();
    m_jumpCount = 1;
}

Player::~Player() { delete m_pInputDevice; }

void Player::update() {
    Body::update();
    std::vector<InputAction> actions = m_pInputDevice->getActions();

    b2Vec2 moveVector;
    moveVector.x = 0.0f;
    moveVector.y = m_pBody->GetLinearVelocity().y;

    for (InputAction action : actions) {
        if (action == InputAction::RIGHT) {
            moveVector.x = 15.0f;
        } else if (action == InputAction::LEFT) {
            moveVector.x = -15.0f;
        } else if (action == InputAction::JUMP && m_jumpCount > 0) {
            moveVector.y = 30.0f;
            m_jumpCount--;
        }
    }

    m_pBody->SetLinearVelocity(moveVector);
}

void Player::landing() { m_jumpCount = 1; }