#include "player.h"
#include "game.h"
#include "animated_sprite.h"
#include "graphics.h"
#include <cmath>

namespace {
    const float kSlowDownFactor = 0.8f;
    const float kWalkingAcceleration = 0.0012f; // (px per ms) / ms  ((px per ms) per ms)
    const float kMaxSpeedX = 0.325f;  // px per ms
    const float kMaxSpeedY = 0.325f;
    const float kJumpSpeed = 0.325f;  // Jump speed in px per ms
    const int kJumpTime = 275;        // time in ms
    const float kGravity = 0.0012f;
}

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b) {
    if (a.motion_type != b.motion_type) {
        return a.motion_type < b.motion_type;
    }
    if (a.horizontal_facing != b.horizontal_facing) {
        return a.horizontal_facing < b.horizontal_facing;
    }
    return false;
}

Player::Player(Graphics& graphics, int x, int y) : 
        x_(x), y_(y), 
        velocity_x_(0.0f), velocity_y_(0.0f),  // initial move and jump velocity
        acceleration_x_(0.0f), 
        horizontal_facing_(RIGHT),
        on_ground_(false) {
            initializeSprites(graphics);
};

void Player::update(int elapsed_time_ms) {
    sprites_[getSpriteState()] -> update(elapsed_time_ms);
    jump_.update(elapsed_time_ms);  // call jump update

    x_ += round(velocity_x_ * elapsed_time_ms); // round since x is int and velocity is float
    velocity_x_ += acceleration_x_ * elapsed_time_ms;
    if (acceleration_x_ < 0.0f) { // if you accelerate left,
        velocity_x_ = std::max(velocity_x_, -kMaxSpeedX);
    }
    else if (acceleration_x_ > 0.0f) { // if you accelerate right
        velocity_x_ = std::min(velocity_x_, kMaxSpeedX);
    }
    else if (on_ground()){  
        velocity_x_ *= kSlowDownFactor;  // no acceleration
    }

    y_ += round(velocity_y_ * elapsed_time_ms);  // update y value on jump
    if (!jump_.active()) {  // if jump is already active, do nothing
        velocity_y_ = std::min( velocity_y_ + (kGravity * elapsed_time_ms), kMaxSpeedY);
    }

    // TODO: Add collision detection with ground here:
    if (y_ >= 320) {  // placeholder ground
        y_ = 320;
        velocity_y_ = 0.0f;
    }
    on_ground_ = (y_ == 320);
    // TODO: END OF TODO.

}
void Player::draw(Graphics& graphics) {
    sprites_[getSpriteState()] -> draw(graphics, x_, y_);
}

void Player::startMovingLeft() {
    acceleration_x_ = -kWalkingAcceleration;
    horizontal_facing_ = LEFT;
};
void Player::startMovingRight() {
    acceleration_x_ = kWalkingAcceleration;
    horizontal_facing_ = RIGHT;
};
void Player::stopMoving() {
    acceleration_x_ = 0.0f;
};

void Player::startJump(){
    if (on_ground()) {                  // If we are on the ground,
        jump_.reset();                  // reset jump and 
        velocity_y_ = -kJumpSpeed;      // assign sprite initial velocity
    }
    else if (velocity_y_ < 0.0f) {      // else if mid jump, 
        jump_.reactivate();             // reactivate jump
    }
}
void Player::stopJump(){                // Deactivate jump (activate gravity)
    jump_.deactivate();
}

void Player::initializeSprites(Graphics& graphics) {
    sprites_[SpriteState(STANDING, RIGHT)] = boost::shared_ptr<Sprite>(new Sprite(graphics,
    "content/kakashi.bmp", 0, 90, Game::kTileSize, Game::kTileSize));

    sprites_[SpriteState(WALKING, RIGHT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
    "content/kakashi.bmp", 0, 270, Game::kTileSize, Game::kTileSize, 15, 6));

    sprites_[SpriteState(STANDING, LEFT)] = boost::shared_ptr<Sprite>(new Sprite(graphics,
    "content/kakashi.bmp", 810, 90, Game::kTileSize, Game::kTileSize));

    sprites_[SpriteState(WALKING, LEFT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics,
    "content/kakashi.bmp", 555, 270, Game::kTileSize, Game::kTileSize, 15, 6));

}

Player::SpriteState Player::getSpriteState() {
    return SpriteState(acceleration_x_ == 0.0f ? STANDING : WALKING, horizontal_facing_);
};

void Player::Jump::reset() {
    time_remaining_ms_ = kJumpTime;
    reactivate();
}

void Player::Jump::update(int elapsed_time_ms) {
    if (active_) {
        time_remaining_ms_ -= elapsed_time_ms;
        if (time_remaining_ms_ <= 0) {
            active_ = false;
        }
    }
}