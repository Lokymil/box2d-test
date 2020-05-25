#include "Player.hpp"

#include <vector>

#include "./PlayerStates/Midair.hpp"
#include "./PlayerStates/Standing.hpp"

// ===== Player state =====

PlayerState::PlayerState(Player* player) : m_pPlayer(player) {}

PlayerState::~PlayerState() {}

void PlayerState::handleInput(std::vector<InputAction> actions) {}

// ===== Player =====

Player::Player(b2Body* body) : Body(body) {
    type = BodyType::PLAYER;
    m_pState = new Standing(this);
    m_healthPoints = 100;
    m_pInputDevice = new InputDevice();
}

Player::~Player() { delete m_pInputDevice; }

void Player::update() {
    Body::update();
    std::vector<InputAction> actions = m_pInputDevice->getActions();

    m_pState->handleInput(actions);
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

b2Vec2 Player::getMovement() { return m_pBody->GetLinearVelocity(); }

void Player::move(b2Vec2 moveVector) { m_pBody->SetLinearVelocity(moveVector); }

void Player::landing() {
    delete m_pState;
    m_pState = new Standing(this);
}

void Player::midair() {
    delete m_pState;
    m_pState = new Midair(this);
}