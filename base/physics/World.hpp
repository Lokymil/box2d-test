#ifndef WORLD_H_
#define WORLD_H_

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>

#define DEFAULT_GRAVITY -80.0f

class World {
   private:
    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
    b2Vec2 m_gravity;

   public:
    b2World* m_pWorld;

   public:
    World();
    ~World();
    b2Body* init();
    b2Body* getBodyList();
    void step();
};

#endif