#include "game.h"
#include <SDL/SDL.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_timer.h>

namespace {
    const int kScreenWidth = 640;
    const int kScreenHeight = 480;
    const int kBitsPerPixel = 32;
    const int kFPS = 60;
}

// Constructor
Game::Game(){
    SDL_Init(SDL_INIT_EVERYTHING); // initialize sdl2
    SDL_ShowCursor(SDL_DISABLE);
    screen_ = SDL_SetVideoMode(
                                kScreenWidth, 
                                kScreenHeight, 
                                kBitsPerPixel, 
                                SDL_FULLSCREEN);
    eventLoop();    // Infinite loop containing everything
}
// Destructor
Game::~Game(){
    SDL_FreeSurface(screen_);
    SDL_Quit();     // quit sdl
}

// while (running) ~ 60hz
// Handle events: input, timer callbacks, 
// update() everything: move everything that moves, check collisions
// Draw() everything
void Game::eventLoop(){
    SDL_Event event;    // Event handler

    bool running = true;
    while (running){
        const int start_time_ms = SDL_GetTicks();   // Get ticks returns elapsed miliseconds since sdl init
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_KEYDOWN:       // Condition to exit if escape is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        running = false;
                    }
                    break;
                default:
                    break;
            }
        }

        update();   // instantiate update and draw methods
        draw();
        // ensure loop lasts 1/60 of a second or 1000/60ths of millisecond
        const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        SDL_Delay(1000/kFPS - elapsed_time_ms);  // (1000ms / 60 fps ms) minus time elapsed doing poll to maintain 60fps
    }
}

void Game::update(){}
void Game::draw(){}