#include "Midair.hpp"

#include <Box2D/Common/b2Math.h>

Midair::Midair(Player* player) : PlayerState(player) {}

Midair::~Midair() {}

void Midair::handleInput(std::vector<InputAction> actions) {
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
}