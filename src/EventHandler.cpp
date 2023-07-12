#include "EventHandler.h"


EventHandler::EventHandler(std::shared_ptr<PolygonLoader> polygonLoader,  std::pair<float, float> camera) {
    this->polygonLoader = polygonLoader;
    this->currentCameraPosition = camera;
}



void EventHandler::handle_event(int quad_id) {
    if (this->event.type == SDL_KEYDOWN) {
        LOG("SDL KEYDOWN received");
        if (this->event.key.keysym.sym == SDLK_LEFT) {
            LOG("move left");
            std::pair<float, float> coords = polygonLoader->getQuadCoordinates(quad_id);
            polygonLoader->moveQuadTo(quad_id, coords.first - 0.01f, coords.second);
        }
        if (this->event.key.keysym.sym == SDLK_RIGHT) {
            LOG("move right");
            std::pair<float, float> coords = polygonLoader->getQuadCoordinates(quad_id);
            polygonLoader->moveQuadTo(quad_id, coords.first + 0.01f, coords.second);
        }
        if (this->event.key.keysym.sym == SDLK_DOWN) {
            LOG("move down");
            std::pair<float, float> coords = polygonLoader->getQuadCoordinates(quad_id);
            polygonLoader->moveQuadTo(quad_id, coords.first, coords.second - 0.01f);
        }
        if (this->event.key.keysym.sym == SDLK_UP) {
            LOG("move up");
            std::pair<float, float> coords = polygonLoader->getQuadCoordinates(quad_id);
            polygonLoader->moveQuadTo(quad_id, coords.first, coords.second + 0.01f);
        }
        if (this->event.key.keysym.sym == SDLK_w) {
            polygonLoader->setCameraCoordinate(currentCameraPosition.first, currentCameraPosition.second + 0.01f);
            currentCameraPosition.second += 0.01f;
        }
        if (this->event.key.keysym.sym == SDLK_a) {
            polygonLoader->setCameraCoordinate(currentCameraPosition.first - 0.01f, currentCameraPosition.second);
            currentCameraPosition.first -= 0.01f;
        }
        if (this->event.key.keysym.sym == SDLK_s) {
            polygonLoader->setCameraCoordinate(currentCameraPosition.first, currentCameraPosition.second - 0.01f);
            currentCameraPosition.second -= 0.01f;
        }
        if (this->event.key.keysym.sym == SDLK_d) {
            polygonLoader->setCameraCoordinate(currentCameraPosition.first + 0.01f, currentCameraPosition.second);
            currentCameraPosition.first += 0.01f;
        }
    }
}

int EventHandler::poll() {
    int poll_return = SDL_PollEvent(&this->event);
    if (this->event.type == SDL_QUIT || this->event.type == SDL_MOUSEBUTTONDOWN){
        this->quit = true;
    }
    return poll_return;
}

bool EventHandler::getQuit() {
    return this->quit;
}