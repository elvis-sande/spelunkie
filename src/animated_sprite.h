#ifndef ANIMATED_SPRITE_H_
#define ANIMATED_SPRITE_H_

#include "sprite.h"

// inherits from Sprite class (public inheritance)
struct AnimatedSprite : public Sprite{
    AnimatedSprite(Graphics& graphics,
                    const std::string& file_path,    // string for filepath
                    int source_x, int source_y,     // where to look for specific sprite in spritesheet
                    int width, int height,
                    int fps, int num_frames);       // additional fps and total number of frames for animation
    
    void update(int elapsed_time_ms);

    private:
    const int frame_time_;  // how many frames we want to run in a second?
    const int num_frames_;
    int current_frame_;
    int elapsed_time_;   // elapsed time since last frame change
};

#endif // ANIMATED_SPRITE