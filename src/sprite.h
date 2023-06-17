#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include <SDL/SDL.h>

struct Graphics;

struct Sprite {
    Sprite(Graphics& graphics,
            const std::string& file_path,    // string for filepath
            int source_x, int source_y,     // where to look for specific sprite in spritesheet
            int width, int height);         // width & height   
    

    virtual void update(int ){};  // update method that takes elapsed time in ms

    // Draw method
    void draw(Graphics& graphics, int x, int y);

    protected:
    SDL_Rect source_rect_; // protected since we will be changing where the source rect is pointing to

    private:
    SDL_Surface* sprite_sheet_;
    
};

#endif // SPRITE_H_