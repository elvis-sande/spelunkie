#include "game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include "graphics.h"
#include "animated_sprite.h"

namespace {     // anonymous namespace with constant values
    const int kFPS = 60;
}

int Game::kTileSize = 100;

// Constructor
Game::Game(){
    SDL_Init(SDL_INIT_EVERYTHING); // initialize sdl2
    SDL_ShowCursor(SDL_DISABLE);
    eventLoop();    // Infinite loop containing everything
}
// Destructor
Game::~Game(){
    SDL_Quit();     // quit sdl
}

// while (running) ~ 60hz
// Handle events: input, timer callbacks, 
// update() everything: move everything that moves, check collisions
// Draw() everything
void Game::eventLoop(){
    Graphics graphics;  // call graphics 
    SDL_Event event;    // Event handler

    sprite_.reset(new AnimatedSprite(
                        "content/naruto.bmp", 0, 0, kTileSize, kTileSize, 15, 4));

    bool running = true;
    int last_update_time = SDL_GetTicks();

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

        const int current_time_ms = SDL_GetTicks();
        update(current_time_ms - last_update_time); // instantiate update method
        last_update_time = current_time_ms;

        draw(graphics); // instantiate draw method
        // ensure loop lasts 1/60 of a second or 1000/60ths of millisecond
        const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        SDL_Delay(1000/kFPS - elapsed_time_ms);  // (1000ms / 60 fps ms) minus time elapsed doing poll to maintain 60fps
        
        /* Test to visualize fps in terminal */
        const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;  // elapsed time / 1000
        const float fps = 1 / seconds_per_frame;    // how many frames in a second
        printf("fps = %f\n", fps);
    }
}

void Game::update(int elapsed_time_ms){
    sprite_ -> update(elapsed_time_ms);
}
void Game::draw(Graphics& graphics){
    sprite_ -> draw(graphics, 320, 240);
    graphics.flip();
}