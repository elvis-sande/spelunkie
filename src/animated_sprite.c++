#include "animated_sprite.h"
#include "game.h"

AnimatedSprite::AnimatedSprite(const std::string& file_path,    // string for filepath
                    int source_x, int source_y,     // where to look for specific sprite in spritesheet
                    int width, int height,
                    int fps, int num_frames) : 
                        Sprite(file_path, source_x, source_y, width, height), 
                        frame_time_(1000 / fps),
                        num_frames_(num_frames),
                        current_frame_(0),
                        elapsed_time_(0)
                        {}; 

void AnimatedSprite::update(int elapsed_time_ms){
    elapsed_time_ += elapsed_time_ms;
    if (elapsed_time_ > frame_time_){                                    // if current frame has reached it's frame time,
        ++current_frame_;                                               // go to next frame
        elapsed_time_ = 0;                                             // and reset frame timer for next frame
        // update source rect
        if (current_frame_ < num_frames_){                             // check if we are on last frame or there are more frames still in loop
            source_rect_.x += Game::kTileSize;                         // go to next frame if not on last frame
        }
        else {                                                        // if at final frame, move to first frame (reset)
            source_rect_.x -= Game::kTileSize * (num_frames_ - 1);    // calculate width of all frames combined and subtract
            current_frame_ = 0;
        }
    }
}