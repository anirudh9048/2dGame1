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

#ifndef POLYLOADER
#define POLYLOADER
class PolygonLoader {
public:
    PolygonLoader();
    ~PolygonLoader();
    int initPolygonLoader();
    int setCameraCoordinate(float x, float y);

    int renderQuadAtWorldCoord(int quad_id);
    int addQuadAt(float x, float y, float width, float height); // returns the quad_id to the caller
    int renderQuadAt(float x, float y);
    int moveQuadTo(int quad_vao_id, float x, float y);
    std::pair<float, float> getQuadCoordinates(int quad_id);


    int renderLineAtWorldCoord(int line_id);
    int addLineAt(float x1, float y1, float x2, float y2);
    int moveLineTo(int line_id, float x1, float y1, float x2, float y2);
    std::pair<float, float> getLineCoordinates(int line_id);

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
        GLuint vbo_id;
        float center_x;
        float center_y;
        float width;
        float height;
    } quad_t;
    
    void printQuad(quad_t quad);
    void printFloatArr(float f[], int size);

    void addQuadToVertexBuffer(quad_t& quad);

    const char* read_shader_from_source(std::string filename);
    int compile_shader(int shader, const char *src);
    int renderTriangleAt(float x, float y);

    std::vector<quad_t> quads;


    typedef struct point {
        float x;
        float y;
    } point_t;

    typedef struct line {
        int line_id;
        point_t p1;
        point_t p2;
        float *heap_point_data;
        GLuint vaoid;
        GLuint vboid;
    } line_t;

    std::vector<line_t> lines;

    void setLineVertexBuffers(line_t& _line);

    int NUM_VERTICES = 8; // actual number of vertices is this div by 2
    float scale = 0.1f;
    float *vertices;
    GLuint vertexShader;
    GLuint fragmentShader;
    // float xCoord = 0.0f;
    // float yCoord = 0.0f;

    float camera_x = 0.0f;
    float camera_y = 0.0f;
};
#endif