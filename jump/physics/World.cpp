#include "World.hpp"

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>

#include "../game/Ground.hpp"
#include "../game/Player.hpp"
#include "ContactListener.hpp"

World::World() {
    m_gravity.x = 0.0f;
    m_gravity.y = DEFAULT_GRAVITY;
    m_pWorld = new b2World(m_gravity);
    m_pWorld->SetContactListener(new ContactListener());
}

World::~World() { delete m_pWorld; }

b2Body* World::init() {
    addStaticBody(0.0f, -15.0f, 20.0f, 5.0f, BodyType::GROUND);
    addStaticBody(25.2f, -15.0f, 5.0f, 5.0f, BodyType::GROUND);
    addStaticBody(3.0f, -5.5f, 2.0f, 0.5f, BodyType::GROUND);
    addStaticBody(8.0f, -0.5f, 2.0f, 0.5f, BodyType::GROUND);
    addStaticBody(-8.0f, -0.5f, 2.0f, 0.5f, BodyType::GROUND);

    // Player
    b2BodyDef playerDef;
    playerDef.type = b2_dynamicBody;
    playerDef.position.Set(0.0f, -9.0f);

    b2Body* player = m_pWorld->CreateBody(&playerDef);
    player->SetUserData(new Player(player));

    b2PolygonShape playerBox;
    playerBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &playerBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    player->CreateFixture(&fixtureDef);

    return player;
}

void World::addStaticBody(float x, float y, float widthFromOrigin, float heightFromOrigin, BodyType type) {
    // BodyType is unused but will be usefull in a more complex world
    b2BodyDef bodyDef;
    bodyDef.position.Set(x, y);

    b2Body* body = m_pWorld->CreateBody(&bodyDef);
    body->SetUserData(new Ground(body));

    b2PolygonShape groundBox;
    groundBox.SetAsBox(widthFromOrigin, heightFromOrigin);
    body->CreateFixture(&groundBox, 0.0f);
}

b2Body* World::getBodyList() { return m_pWorld->GetBodyList(); }

void World::step() { m_pWorld->Step(timeStep, velocityIterations, positionIterations); }