#ifndef INPUT_DEVICE_H_
#define INPUT_DEVICE_H_

#include <vector>

enum class InputAction { LEFT, RIGHT, TOP, DOWN, JUMP };

class InputDevice {
   public:
    InputDevice();
    std::vector<InputAction> getActions();
};

#endif