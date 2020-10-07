#include "Window.h"


Window::Window(int x, int y, int w, int h, std::string n) {
    std::cout << "Window ctor\n";
    this->xc = x;
    this->yc = y;
    this->width = w;
    this->height = h;
    this->name = n;
    std::cout << "Returning from window ctor\n";
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
    std::cout << "Window dtor\n";
    if (this->context != nullptr) {
        std::cout << "context void * " << this->context << std::endl; 
        SDL_GL_DeleteContext(this->context);
    }
}
