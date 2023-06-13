#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>

struct Player;
struct Graphics;

// Definition of game class
struct Game{
    Game();
    ~Game();

    static int kTileSize;

    private:
    void eventLoop();       // Define eventLoop() method
    void update(int elapsed_time_ms);          // update and draw helper methods
    void draw(Graphics& graphics);

    boost::scoped_ptr<Player> player_;

};

#endif // GAME_H_