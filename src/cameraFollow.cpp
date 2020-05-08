#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>

#include <iostream>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
int WINDOW_RATIO = WINDOW_WIDTH / 2;
float M2P = 20.0f;
float P2M = 1.0f / P2M;

b2Body* bodyToFollow = NULL;

b2Vec2* center = new b2Vec2();

b2World* initWorld() {
    // world definition
    b2Vec2 gravity(0.0f, -10.0f);
    b2World* pWorld = new b2World(gravity);

    // ground body definition
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -15.0f);

    // ground body instanciation in world from definition
    b2Body* groundBody = pWorld->CreateBody(&groundBodyDef);

    // ground shape def as box of 100 units large and 20 units tall
    b2PolygonShape groundBox;
    groundBox.SetAsBox(20.0f, 5.0f);

    // Associate texture to body
    // Static object by definition have no mass then 0 density
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Dynamic body definition
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 20.0f);
    bodyToFollow = pWorld->CreateBody(&bodyDef);

    // shape for dynamic body
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // fixture definition used to link a shape to a body
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    // using fixture to associate shape to body
    bodyToFollow->CreateFixture(&fixtureDef);

    return pWorld;
}

SDL_Window* initWindow() {
    // Notre fenêtre
    SDL_Window* fenetre(0);
    SDL_GLContext contexteOpenGL(0);

    // Initialisation de la SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Erreur lors de l'initialisation de la SDL : %s", SDL_GetError());
        SDL_Quit();

        return NULL;
    }

    // Création de la fenêtre

    fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                               WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (fenetre == 0) {
        SDL_Log("Erreur lors de la creation de la fenetre : %s", SDL_GetError());
        SDL_Quit();

        return NULL;
    }

    // Création du contexte OpenGL

    contexteOpenGL = SDL_GL_CreateContext(fenetre);

    if (contexteOpenGL == 0) {
        SDL_Log("Erreur lors de l'inialisation du context OpenGL : %s", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        SDL_Quit();

        return NULL;
    }

    return fenetre;
}

void draw(b2Body* body) {
    b2Shape* shape = body->GetFixtureList()->GetShape();
    b2Shape::Type type = shape->GetType();
    if (type != b2Shape::Type::e_polygon) {
        return;
    }

    b2Vec2 pos = body->GetPosition();

    // Centered screen boundary
    int leftNDC = center->x * M2P - WINDOW_WIDTH / 2;
    int rightNDC = center->x * M2P + WINDOW_WIDTH / 2;
    int bottomNDC = center->y * M2P - WINDOW_HEIGHT / 2;
    int topNDC = center->y * M2P + WINDOW_HEIGHT / 2;

    b2PolygonShape* polygon = (b2PolygonShape*)shape;
    int verticesNumber = polygon->m_count;
    float vertices[verticesNumber * 2];
    for (int i = 0; i < verticesNumber; i++) {
        b2Vec2 vertex = polygon->m_vertices[i];
        float x = (pos.x + vertex.x) * M2P;
        float y = (pos.y + vertex.y) * M2P;

        // Applying orthogonal projection matrix
        // /!\ all factors MUST BE float otherwise, when shifted from origin (0,0) values won't be exact
        float xNDC = (2 * x / (rightNDC - leftNDC)) - ((rightNDC + leftNDC) * 1.0f / (rightNDC - leftNDC));
        float yNDC = (2 * y / (topNDC - bottomNDC)) - ((topNDC + bottomNDC) * 1.0f / (topNDC - bottomNDC));

        vertices[i * 2] = xNDC;
        vertices[i * 2 + 1] = yNDC;
    }

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_POLYGON, 0, verticesNumber);
    glDisableVertexAttribArray(0);
}

void recenterCamera() {
    if (bodyToFollow == NULL) {
        center->x = 0;
        center->y = 0;
        return;
    }

    b2Vec2 position = bodyToFollow->GetPosition();
    center->x = position.x;
    center->y = position.y;
}

void display(b2World* pWorld) {
    recenterCamera();
    glClear(GL_COLOR_BUFFER_BIT);
    b2Body* body = pWorld->GetBodyList();
    while (body) {
        draw(body);
        body = body->GetNext();
    }
}

int main() {
    SDL_Window* pWindow = initWindow();
    if (pWindow == NULL) {
        return -1;
    }

    b2World* pWorld = initWorld();

    // timestep (/!\ != framerate, do not bind world computation timestep to screen framerate /!\)
    float timeStep = 1.0f / 60.0f;

    // iteration number for velocity and position computation
    // the more iteration the worse performance but the better accuracy
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    Uint32 iterationStart;
    bool running = true;
    SDL_Event event;

    while (running) {
        iterationStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                running = false;
            }
        }

        display(pWorld);

        SDL_GL_SwapWindow(pWindow);
        pWorld->Step(timeStep, velocityIterations, positionIterations);

        if (1000.0 / 60 > SDL_GetTicks() - iterationStart) {
            SDL_Delay(1000.0 / 60 - (SDL_GetTicks() - iterationStart));
        }
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    delete center;
    bodyToFollow = NULL;
    delete pWorld;

    return 0;
}