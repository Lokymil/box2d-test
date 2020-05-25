#include "Standing.hpp"

#include <Box2D/Common/b2Math.h>

Standing::Standing(Player* player) : PlayerState(player) {}

Standing::~Standing() {}

void Standing::handleInput(std::vector<InputAction> actions) {
    b2Vec2 moveVector = m_pPlayer->getMovement();
    moveVector.x = 0.0f;

    for (InputAction action : actions) {
        if (action == InputAction::RIGHT) {
            moveVector.x = 15.0f;
        } else if (action == InputAction::LEFT) {
            moveVector.x = -15.0f;
        } else if (action == InputAction::JUMP) {
            moveVector.y = 30.0f;
            m_pPlayer->midair();
        }
    }

    m_pPlayer->move(moveVector);
}