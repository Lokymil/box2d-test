#ifndef PLAYER_H_
#define PLAYER_H_

#include "../input/InputDevice.hpp"
#include "Body.hpp"

class Player : public Body {
   private:
    int m_healthPoints;
    InputDevice* m_pInputDevice;
    int m_maxJumpCount;
    int m_jumpCount;
    int m_jumpRecoveryTime;

   public:
    Player(b2Body* body);
    ~Player();
    void update();
    void resetJumpCount();
};

#endif