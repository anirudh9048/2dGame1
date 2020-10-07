#include "SDL2/SDL.h"
#include <string>
#include <iostream>

class Window {
public:
    Window(int x, int y, int w, int h, std::string n);
    
    ~Window();


    int createSDLWindowAndContext();
    SDL_Window* getSdlWindow();

private:
    SDL_Window *window = nullptr;
    SDL_GLContext context = nullptr;
    int xc;
    int yc;
    int width;
    int height;
    std::string name;
};