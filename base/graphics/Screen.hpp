#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL2/SDL.h>

#include "../physics/World.hpp"
#include "Camera.hpp"

class Screen {
   private:
    const float M2P = 20.0f;
    const float P2M = 1.0f / M2P;
    SDL_Window* m_pWindow;
    SDL_GLContext m_GLContext;
    Camera* m_pCamera;

   public:
    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;

   private:
    void updateBodyToDraw(b2Body* body);
    void drawBody(b2Body* body);

   public:
    Screen(){};
    Screen(int width, int height) : WINDOW_WIDTH(width), WINDOW_HEIGHT(height){};
    ~Screen();
    int init();
    void setCamera(Camera* camera);
    void displayWorld(World* pWorld);
};

#endif