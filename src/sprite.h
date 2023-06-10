#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include <SDL/SDL.h>

struct Graphics;

struct Sprite {
    Sprite(const std::string& file_path,    // string for filepath
            int source_x, int source_y,     // where to look for specific sprite in spritesheet
            int width, int height);         // width & height   
    virtual ~Sprite();  // virtual since it's being inherited from

    // update method that takes elapsed time in ms
    virtual void update(int ){};

    // Draw method
    void draw(Graphics& graphics, int x, int y);

    protected:
    SDL_Rect source_rect_; // protected since we will be changing where the source rect is pointing to

    private:
    SDL_Surface* sprite_sheet_;
    
};

#endif // SPRITE_H_