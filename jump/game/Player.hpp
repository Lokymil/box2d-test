#ifndef PLAYER_H_
#define PLAYER_H_

#include "../input/InputDevice.hpp"
#include "Body.hpp"

class Player : public Body {
   private:
    enum class STATE { STANDING, MIDAIR };

   private:
    STATE m_state;
    int m_healthPoints;
    InputDevice* m_pInputDevice;
    int m_maxJumpCount;
    int m_jumpCount;
    int m_jumpRecoveryTime;

   private:
    void standingInput(std::vector<InputAction> actions);
    void jumpingInput(std::vector<InputAction> actions);

   public:
    Player(b2Body* body);
    ~Player();
    void update();
    void landing();
    void midair();
};

#endif