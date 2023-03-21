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

int main() {
    LOG("Launching app...");
    
    int result = setupSdl();
    if (result < 0) {
        std::cout << "ERROR: setting up sdl\n";
    }
    
    std::shared_ptr<Window> window = std::make_shared<Window>(50, 50, 800, 500, "Window");
    if (window->createSDLWindowAndContext() < 0) {
        return 1;
    }
    
    std::printf("%s\n%s\n", 
        glGetString(GL_RENDERER),  // e.g. Intel HD Graphics 3000 OpenGL Engine
        glGetString(GL_VERSION)    // e.g. 3.2 INTEL-8.0.61
    );

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    std::shared_ptr<PolygonLoader> polygonLoader = std::make_shared<PolygonLoader>();
    polygonLoader->initPolygonLoader();

    polygonLoader->setCameraCoordinate(0.0f, 0.0f);
    int player_quad = polygonLoader->addQuadAt(0.4f, -0.4f, 0.05f, 0.05f); 

    std::vector<int> world_quads;
    std::vector<int> world_lines;

    // int second_quad = polygonLoader->addQuadAt(0.3f, 0.9f, 0.1f, 0.1f);
    world_quads.push_back(polygonLoader->addQuadAt(0.3f, 0.9f, 0.1f, 0.1f));
    

    world_quads.push_back(polygonLoader->addQuadAt(-0.7f, 0.5f, 0.8f, 0.4f));

    world_quads.push_back(polygonLoader->addQuadAt(0.4f,0.5f, 0.3f, 0.2f));

    world_lines.push_back(polygonLoader->addLineAt(0.5f, -0.5f, 0.2f, 0.1f));

    SDL_Event e;
    std::shared_ptr<EventHandler> eventHandler = std::make_shared<EventHandler>(polygonLoader, std::make_pair<float, float>(0.0f, 0.0f)); 
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
            eventHandler->handle_event(e, player_quad);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        polygonLoader->renderQuadAtWorldCoord(player_quad);
        for (int qid : world_quads) {
            polygonLoader->renderQuadAtWorldCoord(qid);
        }
        for (int lid : world_lines) {
            polygonLoader->renderLineAtWorldCoord(lid);
        }
        SDL_GL_SwapWindow(window->getSdlWindow());
    }
    return 0;
}