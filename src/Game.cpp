#include "Game.h"

Game::Game() {

}

Game::~Game() {
    this->polygonLoader = std::make_shared<PolygonLoader>();
    this->currentCameraPosition = std::make_pair<float, float>(0.0f, 0.0f);
}

void Game::init() {
    this->polygonLoader->initPolygonLoader();
    polygonLoader->setCameraCoordinate(this->currentCameraPosition.first, this->currentCameraPosition.second);
}




void Game::update_state(SDL_Event e) {
    int quad_id = 0;
    if (e.type == SDL_KEYDOWN) {
        LOG("SDL KEYDOWN received");
        if (e.key.keysym.sym == SDLK_LEFT) {
            LOG("move left");
            std::pair<float, float> coords = polygonLoader->getQuadCoordinates(quad_id);
            polygonLoader->moveQuadTo(quad_id, coords.first - 0.01f, coords.second);
        }
        if (e.key.keysym.sym == SDLK_RIGHT) {
            LOG("move right");
            std::pair<float, float> coords = polygonLoader->getQuadCoordinates(quad_id);
            polygonLoader->moveQuadTo(quad_id, coords.first + 0.01f, coords.second);
        }
        if (e.key.keysym.sym == SDLK_DOWN) {
            LOG("move down");
            std::pair<float, float> coords = polygonLoader->getQuadCoordinates(quad_id);
            polygonLoader->moveQuadTo(quad_id, coords.first, coords.second - 0.01f);
        }
        if (e.key.keysym.sym == SDLK_UP) {
            LOG("move up");
            std::pair<float, float> coords = polygonLoader->getQuadCoordinates(quad_id);
            polygonLoader->moveQuadTo(quad_id, coords.first, coords.second + 0.01f);
        }
        if (e.key.keysym.sym == SDLK_w) {
            polygonLoader->setCameraCoordinate(currentCameraPosition.first, currentCameraPosition.second + 0.01f);
            currentCameraPosition.second += 0.01f;
        }
        if (e.key.keysym.sym == SDLK_a) {
            polygonLoader->setCameraCoordinate(currentCameraPosition.first - 0.01f, currentCameraPosition.second);
            currentCameraPosition.first -= 0.01f;
        }
        if (e.key.keysym.sym == SDLK_s) {
            polygonLoader->setCameraCoordinate(currentCameraPosition.first, currentCameraPosition.second - 0.01f);
            currentCameraPosition.second -= 0.01f;
        }
        if (e.key.keysym.sym == SDLK_d) {
            polygonLoader->setCameraCoordinate(currentCameraPosition.first + 0.01f, currentCameraPosition.second);
            currentCameraPosition.first += 0.01f;
        }
    }
}

void Game::render() {

}