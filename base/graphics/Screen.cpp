#include "Screen.hpp"

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <GL/gl.h>
#include <GLES3/gl3.h>

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

    m_pWindow = SDL_CreateWindow("Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                                 SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

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
    b2Vec2 pov = m_pCamera->getPosition();
    b2Vec2 bodyCenter = body->GetPosition();

    float left = pov.x * M2P - WINDOW_WIDTH / 2;
    float right = pov.x * M2P + WINDOW_WIDTH / 2;
    float bottom = pov.y * M2P - WINDOW_HEIGHT / 2;
    float top = pov.y * M2P + WINDOW_HEIGHT / 2;

    glm::mat4 projMatrix = glm::ortho(left, right, bottom, top);

    drawCenter(projMatrix, bodyCenter);

    b2Fixture* fixture = body->GetFixtureList();
    while (fixture) {
        b2Shape* shape = fixture->GetShape();
        b2Shape::Type shapeType = shape->GetType();
        switch (shapeType) {
            case b2Shape::e_polygon:
                drawPolygon(projMatrix, bodyCenter, (b2PolygonShape*)shape);
                break;
            case b2Shape::e_edge:
                drawEdge(projMatrix, bodyCenter, (b2EdgeShape*)shape);
                break;
            default:
                break;
        }

        fixture = fixture->GetNext();
    }
}

void Screen::drawPolygon(glm::mat4 projMatrix, b2Vec2 bodyCenter, b2PolygonShape* shape) {
    int verticesNumber = shape->m_count;
    float vertices[verticesNumber * 2];

    for (int i = 0; i < verticesNumber; i++) {
        b2Vec2 vertex = shape->m_vertices[i];

        glm::vec4 posVertex;
        posVertex.x = (bodyCenter.x + vertex.x) * M2P;
        posVertex.y = (bodyCenter.y + vertex.y) * M2P;
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

void Screen::drawEdge(glm::mat4 projMatrix, b2Vec2 bodyCenter, b2EdgeShape* shape) {
    glm::vec4 vertex1;
    vertex1.x = (bodyCenter.x + shape->m_vertex1.x) * M2P;
    vertex1.y = (bodyCenter.y + shape->m_vertex1.y) * M2P;
    vertex1.z = 0;
    vertex1.w = 1;
    glm::vec4 vertex1NDC = projMatrix * vertex1;

    glm::vec4 vertex2;
    vertex2.x = (bodyCenter.x + shape->m_vertex2.x) * M2P;
    vertex2.y = (bodyCenter.y + shape->m_vertex2.y) * M2P;
    vertex2.z = 0;
    vertex2.w = 1;
    glm::vec4 vertex2NDC = projMatrix * vertex2;

    glBegin(GL_LINES);
    glVertex2f(vertex1NDC.x, vertex1NDC.y);
    glVertex2f(vertex2NDC.x, vertex2NDC.y);
    glEnd();
}

void Screen::drawCenter(glm::mat4 projMatrix, b2Vec2 bodyCenter) {
    glm::vec4 vertex;
    vertex.x = bodyCenter.x * M2P;
    vertex.y = bodyCenter.y * M2P;
    vertex.z = 0;
    vertex.w = 1;
    glm::vec4 vertexNDC = projMatrix * vertex;

    glBegin(GL_LINES);
    glVertex2f(vertexNDC.x - 0.01f, vertexNDC.y);
    glVertex2f(vertexNDC.x + 0.01f, vertexNDC.y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(vertexNDC.x, vertexNDC.y - 0.01f);
    glVertex2f(vertexNDC.x, vertexNDC.y + 0.01f);
    glEnd();
}