#include "InputDevice.hpp"

#include <SDL2/SDL.h>

InputDevice::InputDevice() {}

std::vector<InputAction> InputDevice::getActions() {
    std::vector<InputAction> actions;

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        actions.push_back(InputAction::RIGHT);
    } else if (keyboardState[SDL_SCANCODE_LEFT]) {
        actions.push_back(InputAction::LEFT);
    }

    if (keyboardState[SDL_SCANCODE_UP]) {
        actions.push_back(InputAction::JUMP);
    }

    return actions;
}