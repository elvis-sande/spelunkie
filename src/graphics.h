#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <map>

struct SDL_Surface;
struct SDL_Rect;

struct Graphics
{

        typedef SDL_Surface *SurfaceID;

        Graphics();
        ~Graphics();

        SurfaceID loadImage(const std::string &file_path);  // takes standard string of filepath

        // wrapper for drawning method
        void blitSurface(
            SurfaceID source,
            SDL_Rect *source_rectangle,
            SDL_Rect *destination_rectangle);

        void flip();
        void clearScreen(); // trying to fix sprite trail issue

private:
        typedef std::map<std::string, SDL_Surface*> SpriteMap;
        SpriteMap sprite_sheets_;  //map from string to sdl surface pointer called sprite_sheets_

        SDL_Surface *screen_;
};

#endif // GRAPHICS_H_