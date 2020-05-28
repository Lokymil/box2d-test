#ifndef MIDAIR_H_
#define MIDAIR_H_

#include "../Player.hpp"

class Midair : public PlayerState {
   private:
    int m_jumpCount;
    int m_jumpRecovery;

   public:
    Midair(Player* player, int jumpCount);
    ~Midair() override;
    void handleInput(std::vector<InputAction> actions) override;
};

#endif