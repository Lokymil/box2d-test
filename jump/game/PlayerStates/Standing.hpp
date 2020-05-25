#ifndef STANDING_H_
#define STANDING_H_

#include "../Player.hpp"

class Standing : public PlayerState {
   public:
    Standing(Player* player);
    ~Standing() override;
    void handleInput(std::vector<InputAction> actions) override;
};

#endif