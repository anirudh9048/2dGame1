#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> 

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include "PolygonLoader.h"
#include "SDL2/SDL.h"

#ifndef GAME
#define GAME
class Game {
public:
    Game();
    ~Game();
    void init();
    void init_game_state();
    void update_state(SDL_Event e);
    void render();
private:
    std::shared_ptr<PolygonLoader> polygonLoader;
    std::pair<float, float> currentCameraPosition; 
};
#endif
