#include "Screen.hpp"

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <GL/gl.h>
#include <GLES3/gl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../game/Body.hpp"

Screen::~Screen() {
    SDL_GL_DeleteContext(m_GLContext);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

int Screen::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Error on SDL initialization: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    m_pWindow = SDL_CreateWindow("Root of all evil", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                 WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (m_pWindow == NULL) {
        SDL_Log("Error on window creation: %s", SDL_GetError());
        SDL_Quit();

        return -2;
    }

    m_GLContext = SDL_GL_CreateContext(m_pWindow);
    if (m_GLContext == NULL) {
        SDL_Log("Error on GL context creation: %s", SDL_GetError());
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();

        return -3;
    }

    return 0;
}

void Screen::setCamera(Camera* pCamera) { m_pCamera = pCamera; }

void Screen::displayWorld(World* pWorld) {
    m_pCamera->centerOnPlayer();
    glClear(GL_COLOR_BUFFER_BIT);

    b2Body* body = pWorld->getBodyList();
    while (body) {
        updateBodyToDraw(body);
        drawBody(body);
        body = body->GetNext();
    }

    SDL_GL_SwapWindow(m_pWindow);
}

void Screen::updateBodyToDraw(b2Body* body) {
    Body* userBody = (Body*)body->GetUserData();
    userBody->update();
}

void Screen::drawBody(b2Body* body) {
    b2Shape* shape = body->GetFixtureList()->GetShape();
    b2Shape::Type type = shape->GetType();
    if (type != b2Shape::Type::e_polygon) {
        return;
    }

    b2Vec2 pov = m_pCamera->getPosition();
    b2Vec2 pos = body->GetPosition();

    float left = pov.x * M2P - WINDOW_WIDTH / 2;
    float right = pov.x * M2P + WINDOW_WIDTH / 2;
    float bottom = pov.y * M2P - WINDOW_HEIGHT / 2;
    float top = pov.y * M2P + WINDOW_HEIGHT / 2;

    glm::mat4 projMatrix = glm::ortho(left, right, bottom, top);

    b2PolygonShape* polygon = (b2PolygonShape*)shape;
    int verticesNumber = polygon->m_count;
    float vertices[verticesNumber * 2];

    for (int i = 0; i < verticesNumber; i++) {
        b2Vec2 vertex = polygon->m_vertices[i];

        glm::vec4 posVertex;
        posVertex.x = (pos.x + vertex.x) * M2P;
        posVertex.y = (pos.y + vertex.y) * M2P;
        posVertex.z = 0;
        posVertex.w = 1;

        glm::vec4 posNDC = projMatrix * posVertex;
        vertices[i * 2] = posNDC.x;
        vertices[i * 2 + 1] = posNDC.y;
    }

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_POLYGON, 0, verticesNumber);
    glDisableVertexAttribArray(0);
}