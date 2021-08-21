#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> 

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#define LOG_ENABLED
#include "Log.h"

class PolygonLoader {
public:
    PolygonLoader();
    ~PolygonLoader();
    int initPolygonLoader();

    int renderQuadAtWorldCoord(int quad_id);
    int setCameraCoordinate(float x, float y);
    int addQuadAt(float x, float y); // returns the quad_id to the caller
    int renderQuadAt(float x, float y);

    int moveQuadTo(int quad_vao_id, float x, float y);
private:
    typedef struct quad_vertex {
        float x;
        float y;
    } quad_vertex_t;

    typedef struct quad {
        int quad_id;
        quad_vertex_t vertices[4];
        float *heap_vertex_data;
        GLuint vao_id;
    } quad_t;
    
    void printQuad(quad_t quad);
    void printFloatArr(float f[], int size);

    int addQuadToVertexBuffer(quad_t quad);

    const char* read_shader_from_source(std::string filename);
    int compile_shader(int shader, const char *src);
    int renderTriangleAt(float x, float y);

    std::vector<quad_t> quads;

    int NUM_VERTICES = 8; // actual number of vertices is this div by 2? 8 const?
    float scale = 0.1f;
    float *vertices;
    GLuint vertexShader;
    GLuint fragmentShader;
    float xCoord = 0.0f;
    float yCoord = 0.0f;

    float camera_x = 0.0f;
    float camera_y = 0.0f;
};