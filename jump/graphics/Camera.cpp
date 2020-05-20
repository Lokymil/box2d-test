#include "Camera.hpp"

Camera::Camera() {
    m_x = 0;
    m_y = 0;
}

Camera::Camera(b2Body* pPlayer) {
    m_pPlayer = pPlayer;
    m_x = pPlayer->GetPosition().x;
    m_y = pPlayer->GetPosition().y;
}

Camera::~Camera() { m_pPlayer = NULL; }

void Camera::centerOnPlayer() {
    m_x = m_pPlayer->GetPosition().x;
    m_y = m_pPlayer->GetPosition().y;
}

b2Vec2 Camera::getPosition() {
    b2Vec2 position(m_x, m_y);
    return position;
}