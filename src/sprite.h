#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include <SDL/SDL.h>

struct Graphics;

struct Sprite {
    Sprite(const std::string& file_path,    // string for filepath
            int source_x, int source_y,     // where to look for specific sprite in spritesheet
            int width, int height);         // width & height   
    ~Sprite();

    // Draw method
    void draw(Graphics& graphics, int x, int y);

    private:
    SDL_Surface* sprite_sheet_;
    SDL_Rect source_rect_;
};

#endif // SPRITE_H_