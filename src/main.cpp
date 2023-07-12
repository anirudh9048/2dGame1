#define GL_SILENCE_DEPRECATION
#define LOG_ENABLED

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Log.h"
#include "Window.h"
#include "PolygonLoader.h"
#include "EventHandler.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> 

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>



int setupSdl() {
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3); //OpenGL 3+
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3); //OpenGL 3.3
    return result;
}

int runTestLoop() {
    // Create SDL Window through custom wrapper
    std::shared_ptr<Window> window = std::make_shared<Window>(50, 50, 800, 500, "Window");
    if (window->createSDLWindowAndContext() < 0) {
        std::cout << "ERROR: SDL windown and context creation failed\n";
        return -1;
    }
    
    std::printf("%s\n%s\n", 
        glGetString(GL_RENDERER),  // e.g. Intel HD Graphics 3000 OpenGL Engine
        glGetString(GL_VERSION)    // e.g. 3.2 INTEL-8.0.61
    );

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Create PolygonLoader
    std::shared_ptr<PolygonLoader> polygonLoader = std::make_shared<PolygonLoader>();
    polygonLoader->initPolygonLoader();

    polygonLoader->setCameraCoordinate(0.0f, 0.0f);
    float player_color[] = {0.5f,0.5f,0.0f};
    int player_quad = polygonLoader->addQuadAt(0.4f, -0.4f, 0.05f, 0.05f, player_color); 

    std::vector<int> world_quads;
    std::vector<int> world_lines;

    float building_color[] = {0.0f,0.0f,1.0f};
    world_quads.push_back(polygonLoader->addQuadAt(0.3f, 0.9f, 0.1f, 0.1f, building_color));
    world_quads.push_back(polygonLoader->addQuadAt(-0.7f, 0.5f, 0.8f, 0.4f, building_color));
    world_quads.push_back(polygonLoader->addQuadAt(0.4f,0.5f, 0.3f, 0.2f, building_color));

    world_lines.push_back(polygonLoader->addLineAt(0.5f, -0.5f, 0.2f, 0.1f));

    // Create EventHandler
    // only use EventHandler for running this dummy test loop
    SDL_Event e;
    std::shared_ptr<EventHandler> eventHandler = std::make_shared<EventHandler>(polygonLoader, std::make_pair<float, float>(0.0f, 0.0f)); 
    bool quit = false;
    
    while (!quit){
        while (eventHandler->poll()){
            if (eventHandler->getQuit()) {
                quit = true;
            }
            eventHandler->handle_event(player_quad);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        polygonLoader->renderQuadAtWorldCoord(player_quad);
        for (int qid : world_quads) {
            polygonLoader->renderQuadAtWorldCoord(qid);
        }
        for (int lid : world_lines) {
            polygonLoader->renderLineAtWorldCoord(lid);
        }
        window->swapWindow();
    }
    return 0;
}

int main() {
    LOG("Launching app...");
    
    // Global SDL init
    int result = setupSdl();
    if (result < 0) {
        std::cout << "ERROR: SDL setup failed\n";
        return -1;
    }
     
    int ret = runTestLoop();
    return ret;
}