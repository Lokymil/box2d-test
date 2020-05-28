#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

#include "../input/InputDevice.hpp"
#include "Body.hpp"

// ===== Player state =====

class Player;

enum class PlayerStateType { LANDING, STANDING, MIDAIR };

class PlayerState {
   protected:
    Player* m_pPlayer;
    PlayerStateType m_stateType;

   public:
    PlayerState(Player* player);
    virtual ~PlayerState();
    virtual void handleInput(std::vector<InputAction> actions);
    const PlayerStateType getStateType();
};

//===== Player =====

class Player : public Body {
   private:
    std::unique_ptr<PlayerState> m_pState;
    int m_healthPoints;
    InputDevice* m_pInputDevice;
    int m_maxJumpCount;

   private:
    void standingInput(std::vector<InputAction> actions);
    void jumpingInput(std::vector<InputAction> actions);

   public:
    Player(b2Body* body);
    ~Player();
    void update();
    b2Vec2 getMovement();
    void move(b2Vec2 moveVector);
    void land();
    void stand();
    void midair();
};

#endif