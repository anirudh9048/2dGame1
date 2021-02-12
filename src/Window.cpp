#include "Window.h"


Window::Window(int x, int y, int w, int h, std::string n) {
    this->xc = x;
    this->yc = y;
    this->width = w;
    this->height = h;
    this->name = n;
}


int Window::createSDLWindowAndContext() {
    this->window = SDL_CreateWindow(this->name.c_str(), this->xc, this->yc, this->width, this->height, SDL_WINDOW_OPENGL);
    if (this->window == nullptr) {
        return -1;
    }
    this->context = SDL_GL_CreateContext(this->window);
    if (this->context == nullptr) {
        return -1;
    }
    return 0;
}

    
SDL_Window* Window::getSdlWindow() {
    return this->window;
}

Window::~Window() {
    if (this->context != nullptr) {
        SDL_GL_DeleteContext(this->context);
    }
}
