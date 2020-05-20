#ifndef BODY_H_
#define BODY_H_

#include <Box2D/Dynamics/b2Body.h>

enum class BodyType { GROUND, PLAYER };

class Body {
   public:
    BodyType type;
    b2Body* m_pBody;

   public:
    Body(b2Body* body);
    virtual ~Body();
    void virtual update();
};

#endif