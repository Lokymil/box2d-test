#include "ContactListener.hpp"

#include "../game/Body.hpp"
#include "../game/Player.hpp"

void ContactListener::BeginContact(b2Contact* contact) {
    b2ContactListener::BeginContact(contact);
    Body* bodyA = (Body*)contact->GetFixtureA()->GetBody()->GetUserData();
    Body* bodyB = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyA->type == BodyType::PLAYER && bodyB->type == BodyType::GROUND) {
        ((Player*)bodyA)->land();
    } else if (bodyB->type == BodyType::PLAYER && bodyA->type == BodyType::GROUND) {
        ((Player*)bodyB)->land();
    }
}

void ContactListener::EndContact(b2Contact* contact) { b2ContactListener::EndContact(contact); }