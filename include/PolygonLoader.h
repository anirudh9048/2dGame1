#include <iostream>
#include <string>
#include <fstream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> 

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

class PolygonLoader {
public:
    PolygonLoader();
    ~PolygonLoader();
    int initPolygonLoader();

    int renderQuadAtWorldCoord(float x, float y);
    int setCameraCoordinate(float x, float y);

private:
    const char* read_shader_from_source(std::string filename);
    int compile_shader(int shader, const char *src);
    int renderTriangleAt(float x, float y);
    int renderQuadAt(float x, float y);

    const int NUM_VERTICES = 8;
    float scale = 0.1f;
    float *vertices;
    GLuint vertexShader;
    GLuint fragmentShader;
    float xCoord = 0.0f;
    float yCoord = 0.0f;

    float camera_x = 0.0f;
    float camera_y = 0.0f;
};