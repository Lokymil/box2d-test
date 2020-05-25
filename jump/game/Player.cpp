#include "Player.hpp"

#include <Box2D/Dynamics/Contacts/b2Contact.h>

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
    m_maxJumpCount = 2;
}

Player::~Player() { delete m_pInputDevice; }

void Player::update() {
    Body::update();

    std::vector<InputAction> actions = m_pInputDevice->getActions();

    m_pState->handleInput(actions);
}

b2Vec2 Player::getMovement() { return m_pBody->GetLinearVelocity(); }

void Player::move(b2Vec2 moveVector) { m_pBody->SetLinearVelocity(moveVector); }

void Player::landing() {
    delete m_pState;
    m_pState = new Standing(this);
}

void Player::midair() {
    delete m_pState;
    m_pState = new Midair(this, m_maxJumpCount - 1);
}