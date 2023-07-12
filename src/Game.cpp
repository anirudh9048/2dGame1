#include "Game.h"

Game::Game() {
    this->polygonLoader = std::make_shared<PolygonLoader>();
    this->currentCameraPosition = std::make_pair<float, float>(0.0f, 0.0f);
}

Game::~Game() {
    
}

void Game::init() {
    this->polygonLoader->initPolygonLoader();
    polygonLoader->setCameraCoordinate(this->currentCameraPosition.first, this->currentCameraPosition.second);
}

void Game::init_game_state() {
    
}

void Game::run() {
    while(this->running) {
        while (SDL_PollEvent(&this->event)) {
            if (this->event.type == SDL_QUIT || this->event.type == SDL_MOUSEBUTTONDOWN) {
                this->running = false;
                break;
            }
        }
        update_state(this->event);
        render();
    }
}


void Game::update_state(SDL_Event e) {
    LOG("This should not be called!");
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    // foreach item in world 
    // this->polygonLoader->renderShapeAtWorldCoord(shape_id)
    this->polygonLoader->renderQuadAtWorldCoord(0);
    this->window->swapWindow();
}