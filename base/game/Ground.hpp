#ifndef GROUND_H_
#define GROUND_H_

#include "Body.hpp"

class Ground : public Body {
   public:
    Ground(b2Body* body);
    void update();
};

#endif