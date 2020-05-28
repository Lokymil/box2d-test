#include "ContactListener.hpp"

#include "../game/Body.hpp"
#include "../game/Player.hpp"
#include "World.hpp"

void ContactListener::BeginContact(b2Contact* contact) {
    b2ContactListener::BeginContact(contact);

    FixtureType* typeFixtureA = (FixtureType*)contact->GetFixtureA()->GetUserData();
    FixtureType* typeFixtureB = (FixtureType*)contact->GetFixtureB()->GetUserData();

    if (*typeFixtureA == FixtureType::PLAYER) {
        if (*typeFixtureB == FixtureType::FLOOR) {
            ((Player*)contact->GetFixtureA()->GetBody()->GetUserData())->land();
        }
    } else if (*typeFixtureB == FixtureType::PLAYER) {
        if (*typeFixtureA == FixtureType::FLOOR) {
            ((Player*)contact->GetFixtureB()->GetBody()->GetUserData())->land();
        }
    }
}

void ContactListener::EndContact(b2Contact* contact) { b2ContactListener::EndContact(contact); }