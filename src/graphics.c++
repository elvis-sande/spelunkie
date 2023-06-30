#include "graphics.h"
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

namespace {     // anonymous namespace with constant values
    const int kScreenWidth = 640;
    const int kScreenHeight = 480;
    const int kBitsPerPixel = 32;
}

Graphics::Graphics(){
    screen_ = SDL_SetVideoMode(
                                kScreenWidth, 
                                kScreenHeight, 
                                kBitsPerPixel, 
                                0);
};

Graphics::~Graphics(){
    for (SpriteMap::iterator iter = sprite_sheets_.begin();
        iter != sprite_sheets_.end();
        ++iter) {
            SDL_FreeSurface(iter -> second);
        };
    SDL_FreeSurface(screen_);
};

Graphics::SurfaceID Graphics::loadImage(const std::string& file_path) {
    if (sprite_sheets_.count(file_path) == 0) {     // if no sprite sheet is loaded,
        sprite_sheets_[file_path] = SDL_LoadBMP(file_path.c_str());  // load sprite sheet
    }
    return sprite_sheets_[file_path];
}

// Definition of blitsurface public method
void Graphics::blitSurface(
        SurfaceID source,
        SDL_Rect* source_rectangle,
        SDL_Rect* destination_rectangle
        ) {
            SDL_BlitSurface(source, source_rectangle, screen_, destination_rectangle);
        };

//  Trying to fix sprite trail issue
void Graphics::clearScreen() {
    SDL_FillRect(screen_, NULL, 0); // surface rect, destination rect, uint32 color
}

void Graphics::flip(){
    SDL_Flip(screen_);
};