#ifndef PLAYER_H_
#define PLAYER_H_

#include <boost/shared_ptr.hpp>
#include "sprite.h"
#include <map>


struct Graphics;

struct Player {

    Player(Graphics& graphics, int x, int y);

    void update(int elapsed_time_ms);
    void draw(Graphics& graphics);

    void startMovingLeft();
    void startMovingRight();
    void stopMoving();

    void lookUp();
    void lookDown();
    void lookHorizontal();

    void startJump();
    void stopJump();

    private:
    enum MotionType {
        STANDING,
        WALKING,
        JUMPING,
        FALLING,
    };
    enum HorizontalFacing {
        LEFT,
        RIGHT,
    };
    enum VerticalFacing {
        UP,
        DOWN,
        HORIZONTAL
    };

    struct SpriteState {
        SpriteState(MotionType motion_type = STANDING,    // constructor defaults
                    HorizontalFacing horizontal_facing = RIGHT,
                    VerticalFacing vertical_facing = HORIZONTAL) :
                        motion_type(motion_type),    // constructor initialization
                        horizontal_facing(horizontal_facing),
                        vertical_facing(vertical_facing) {};
        MotionType motion_type;
        HorizontalFacing horizontal_facing;
        VerticalFacing vertical_facing;
    };

    friend bool operator<(const SpriteState& a, const SpriteState& b);

    struct Jump {
    Jump() : time_remaining_ms_(0), active_(false) {};

    void update(int elapsed_time_ms);
    void reset();
    void reactivate() {active_ = time_remaining_ms_ > 0;}  // only true if time remaining > 0
    void deactivate() {active_ = false;}
    bool active() const {return active_;}

    private:
        int time_remaining_ms_;
        bool active_;
};

    void initializeSprites(Graphics& graphics);
    
    SpriteState getSpriteState();

    bool on_ground() const {return on_ground_;};

    int x_, y_;
    float velocity_x_, velocity_y_;  // movement and jump velocity
    float acceleration_x_;
    HorizontalFacing horizontal_facing_;
    VerticalFacing vertical_facing_;
    bool on_ground_;
    Jump jump_;

    std::map<SpriteState, boost::shared_ptr<Sprite>> sprites_;
};

#endif // PLAYER_H_