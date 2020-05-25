#include "Landing.hpp"

#include <Box2D/Common/b2Math.h>

#include "../../physics/World.hpp"

Landing::Landing(Player* player) : PlayerState(player) { m_landRecovery = World::FPS / 6; }

Landing::~Landing() {}

void Landing::handleInput(std::vector<InputAction> actions) {
    b2Vec2 moveVector = m_pPlayer->getMovement();
    moveVector.x = 0.0f;

    for (InputAction action : actions) {
        if (action == InputAction::RIGHT) {
            moveVector.x = 15.0f;
        } else if (action == InputAction::LEFT) {
            moveVector.x = -15.0f;
        }
    }

    m_pPlayer->move(moveVector);

    if (m_landRecovery > 0) {
        m_landRecovery--;
    } else {
        m_pPlayer->standing();
    }
}