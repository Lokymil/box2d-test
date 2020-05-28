#include "Midair.hpp"

#include <Box2D/Common/b2Math.h>

#include "../../physics/World.hpp"

Midair::Midair(Player* player, int jumpCount) : PlayerState(player), m_jumpCount(jumpCount) {
    m_jumpRecovery = World::FPS / 2;
    m_stateType = PlayerStateType::MIDAIR;
}

Midair::~Midair() {}

void Midair::handleInput(std::vector<InputAction> actions) {
    if (m_jumpRecovery > 0) {
        m_jumpRecovery--;
    }

    b2Vec2 moveVector = m_pPlayer->getMovement();
    moveVector.x = 0.0f;

    for (InputAction action : actions) {
        if (action == InputAction::RIGHT) {
            moveVector.x = 15.0f;
        } else if (action == InputAction::LEFT) {
            moveVector.x = -15.0f;
        } else if (action == InputAction::JUMP && m_jumpCount > 0 && m_jumpRecovery <= 0) {
            moveVector.y = 30.0f;
            m_jumpCount--;
            m_jumpRecovery = World::FPS / 2;
        }
    }

    m_pPlayer->move(moveVector);
}