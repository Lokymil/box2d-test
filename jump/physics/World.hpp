#ifndef WORLD_H_
#define WORLD_H_

#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>

#include "../game/Body.hpp"

#define DEFAULT_GRAVITY -80.0f

enum class FixtureType { FLOOR, WALL, CEIL, PLAYER };

class World {
   public:
    const static int FPS = 60;

   private:
    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 10;
    const int32 positionIterations = 8;
    b2Vec2 m_gravity;

   public:
    b2World* m_pWorld;

   private:
    void addStaticBody(float x, float y, float widthFromOrigin, float heightFromOrigin, BodyType type);
    void addEdgeToBody(float x1, float y1, float x2, float y2, b2Body* body, FixtureType type);

   public:
    World();
    ~World();
    b2Body* init();
    b2Body* getBodyList();
    void step();
};

#endif