#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>

#include <iostream>

int main() {
    std::cout << "Hello world !" << std::endl;

    // world definition
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    // ground body definition
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // ground body instanciation in world from definition
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // ground shape def as box of 100 units large and 20 units tall
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    // Associate texture to body
    // Static object by definition have no mass then 0 density
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Dynamic body definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    // shape for dynamic body
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // fixture definition used to link a shape to a body
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    // using fixture to associate shape to body
    body->CreateFixture(&fixtureDef);

    // timestep (/!\ != framerate, do not bind world computation timestep to screen framerate /!\)
    float timeStep = 1.0f / 60.0f;

    // iteration number for velocity and position computation
    // the more iteration the worse performance but the better accuracy
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // 1 sec of simulation
    // Output is only in console to simplify code
    for (int32 i = 0; i < 60; ++i) {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }

    return 0;
}