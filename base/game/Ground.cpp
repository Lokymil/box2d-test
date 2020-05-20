#include "Ground.hpp"

Ground::Ground(b2Body* body) : Body(body) { type = BodyType::GROUND; }

void Ground::update() { Body::update(); }