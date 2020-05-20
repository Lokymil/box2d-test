#ifndef CAMERA_H_
#define CAMERA_H_

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>

class Camera {
   private:
    float m_x;
    float m_y;
    b2Body* m_pPlayer;

   public:
    Camera();
    Camera(b2Body* pPlayer);
    ~Camera();
    void centerOnPlayer();
    b2Vec2 getPosition();
};

#endif