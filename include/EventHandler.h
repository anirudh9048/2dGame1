#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> 

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include "PolygonLoader.h"
#include "SDL2/SDL.h"

class EventHandler {
private:
    std::shared_ptr<PolygonLoader> polygonLoader;
    std::pair<float, float> currentCameraPosition; 
public:
    void handle_event(SDL_Event e, int quad_id);
    EventHandler(std::shared_ptr<PolygonLoader> polygonLoader, std::pair<float, float> camera);
};