#include "Player.hpp"

#include <vector>

Player::Player(b2Body* body) : Body(body) {
    type = BodyType::PLAYER;
    m_state = STATE::STANDING;
    m_healthPoints = 100;
    m_pInputDevice = new InputDevice();
}

Player::~Player() { delete m_pInputDevice; }

void Player::update() {
    Body::update();
    std::vector<InputAction> actions = m_pInputDevice->getActions();

    switch (m_state) {
        case STATE::STANDING:
            standingInput(actions);
            break;
        case STATE::MIDAIR:
            midairInput(actions);
            break;
        default:
            standingInput(actions);
    }
}

void Player::standingInput(std::vector<InputAction> actions) {
    b2Vec2 moveVector;
    moveVector.x = 0.0f;
    moveVector.y = m_pBody->GetLinearVelocity().y;

    for (InputAction action : actions) {
        if (action == InputAction::RIGHT) {
            moveVector.x = 15.0f;
        } else if (action == InputAction::LEFT) {
            moveVector.x = -15.0f;
        } else if (action == InputAction::JUMP) {
            moveVector.y = 30.0f;
            midair();
        }
    }

    m_pBody->SetLinearVelocity(moveVector);
}

void Player::midairInput(std::vector<InputAction> actions) {
    b2Vec2 moveVector;
    moveVector.x = 0.0f;
    moveVector.y = m_pBody->GetLinearVelocity().y;

    for (InputAction action : actions) {
        if (action == InputAction::RIGHT) {
            moveVector.x = 15.0f;
        } else if (action == InputAction::LEFT) {
            moveVector.x = -15.0f;
        }
    }

    m_pBody->SetLinearVelocity(moveVector);
}

void Player::landing() { m_state = STATE::STANDING; }

void Player::midair() { m_state = STATE::MIDAIR; }