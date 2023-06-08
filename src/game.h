#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>

struct Sprite;
struct Graphics;

// Definition of game class
struct Game{
    Game();
    ~Game();

    private:
    void eventLoop();       // Define eventLoop() method
    void update();          // update and draw helper methods
    void draw(Graphics& graphics);

    boost::scoped_ptr<Sprite> sprite_;

};

#endif // GAME_H_