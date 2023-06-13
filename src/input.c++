#include "input.h"

void Input::beginNewFrame(){
    pressed_keys_.clear(); // clear key maps for pressed and released keys
    released_keys_.clear();
};

void Input::keyDownEvent(const SDL_Event& event){
    pressed_keys_[event.key.keysym.sym] = true;
    held_keys_[event.key.keysym.sym] = true;
};

void Input::keyUpEvent(const SDL_Event& event){
    released_keys_[event.key.keysym.sym] = true;
    held_keys_[event.key.keysym.sym] = false; // key is released
};

bool Input::wasKeyPressed(SDLKey key){
    return pressed_keys_[key]; // check key
};

bool Input::wasKeyReleased(SDLKey key){
    return released_keys_[key]; // check key
};

bool Input::isKeyHeld(SDLKey key){
    return held_keys_[key];
};