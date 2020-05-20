#ifndef PLAYER_H_
#define PLAYER_H_

#include "../input/InputDevice.hpp"
#include "Body.hpp"

class Player : public Body {
   private:
    int m_healthPoints;
    InputDevice* m_pInputDevice;
    int m_jumpCount = 0;

   public:
    Player(b2Body* body);
    ~Player();
    void update();
    void resetJumpCount();
};

#endif