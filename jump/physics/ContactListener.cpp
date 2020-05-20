#include "ContactListener.hpp"

void ContactListener::BeginContact(b2Contact* contact) {
    Body* bodyA = (Body*)contact->GetFixtureA()->GetBody()->GetUserData();
    Body* bodyB = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyA->type == BodyType::PLAYER && bodyB->type == BodyType::GROUND) {
        ((Player*)bodyA)->resetJumpCount();
    } else if (bodyB->type == BodyType::PLAYER && bodyA->type == BodyType::GROUND) {
        ((Player*)bodyB)->resetJumpCount();
    }
}

void ContactListener::EndContact(b2Contact* contact) {}