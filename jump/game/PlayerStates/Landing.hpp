#ifndef LANDING_H_
#define LANDING_H_

#include "../Player.hpp"

class Landing : public PlayerState {
   private:
    int m_landRecovery;

   public:
    Landing(Player* player);
    ~Landing() override;
    void handleInput(std::vector<InputAction> actions) override;
};

#endif