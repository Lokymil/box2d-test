#ifndef PLAYER_H_
#define PLAYER_H_

#include "../input/InputDevice.hpp"
#include "Body.hpp"

// ===== Player state =====

class Player;

class PlayerState {
   protected:
    Player* m_pPlayer;

   public:
    PlayerState(Player* player);
    virtual ~PlayerState();
    virtual void handleInput(std::vector<InputAction> actions);
};

//===== Player =====

class Player : public Body {
   private:
    PlayerState* m_pState;
    int m_healthPoints;
    InputDevice* m_pInputDevice;

   private:
    void standingInput(std::vector<InputAction> actions);
    void midairInput(std::vector<InputAction> actions);

   public:
    Player(b2Body* body);
    ~Player();
    void update();
    b2Vec2 getMovement();
    void move(b2Vec2 moveVector);
    void landing();
    void midair();
};

#endif