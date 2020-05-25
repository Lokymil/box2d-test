#ifndef MIDAIR_H_
#define MIDAIR_H_

#include "../Player.hpp"

class Midair : public PlayerState {
   public:
    Midair(Player* player);
    ~Midair() override;
    void handleInput(std::vector<InputAction> actions) override;
};

#endif