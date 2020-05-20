#include "Body.hpp"

Body::Body(b2Body* body) : m_pBody(body) {}

Body::~Body() { m_pBody = NULL; }

void Body::update() {}