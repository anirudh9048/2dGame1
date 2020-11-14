#include <iostream>
#include <string>
#include <vector>
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

    int renderQuadAtWorldCoord(float x, float y, int quad_id);
    int setCameraCoordinate(float x, float y);
    int addQuadAt(float x, float y); // returns the quad_id to the caller
private:
    typedef struct quad_vertex {
        float x;
        float y;
    } quad_vertex_t;

    typedef struct quad {
        int quad_id;
        quad_vertex_t vertices[4];
    } quad_t;
    
    void addQuadToVertexBuffer(quad_t quad);

    const char* read_shader_from_source(std::string filename);
    int compile_shader(int shader, const char *src);
    int renderTriangleAt(float x, float y);
    int renderQuadAt(float x, float y);

    std::vector<quad_t> quads;

    const int NUM_VERTICES = 16; // actual number of vertices is this div by 2? 8
    float scale = 0.1f;
    float *vertices;
    GLuint vertexShader;
    GLuint fragmentShader;
    float xCoord = 0.0f;
    float yCoord = 0.0f;

    float camera_x = 0.0f;
    float camera_y = 0.0f;
};