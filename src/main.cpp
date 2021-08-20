#define GL_SILENCE_DEPRECATION
#define LOG_ENABLED

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Log.h"
#include "Window.h"
#include "PolygonLoader.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> 

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>



GLubyte indices[] = {0,1,2,
                     2,3,0};

int compile_shader(int shader, const char *src) {
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!(status == GL_TRUE)) {
        std::cout << "ERROR COMPILING SHADER\n";
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        std::cout << buffer << std::endl;
        return -1;
    }

    return 0;
}

const char* read_shader_from_source(std::string filename) {
    std::ifstream file(filename);
    if (!file.good()) {
        std::cout << "ERROR opening file " << filename << std::endl;
        return nullptr;
    }
    file.seekg(0, file.end);
    int filelength = file.tellg();
    file.seekg(0, file.beg);
    char *st = new char[filelength+1];
    file.read(st, filelength);
    st[filelength] = '\0';
    return st;
}

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

    glClearColor(0,0,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window->getSdlWindow());
    std::shared_ptr<PolygonLoader> polygonLoader = std::make_shared<PolygonLoader>();
    polygonLoader->initPolygonLoader();

    polygonLoader->setCameraCoordinate(0.0f, 0.5f);

    polygonLoader->renderQuadAt(0.2f, 0.5f);

    int second_quad = polygonLoader->addQuadAt(0.3f, 0.9f);

    polygonLoader->renderQuadAtWorldCoord(second_quad);

    int third_quad = polygonLoader->addQuadAt(0.4f, -0.4f);

    polygonLoader->renderQuadAtWorldCoord(third_quad);
    
    SDL_GL_SwapWindow(window->getSdlWindow());


    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }
    return 0;
}