#ifndef GAME_H_
#define GAME_H_
//#include <SDL2/SDL_surface.h>

struct SDL_Surface;

// Definition of game class
struct Game{
    Game();
    ~Game();

    private:
    void eventLoop();       // Define eventLoop() method
    void update();          // update and draw helper methods
    void draw();

    SDL_Surface* screen_;
};

#endif // GAME_H_