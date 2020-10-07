#include "PolygonLoader.h"

PolygonLoader::PolygonLoader() {
    // these are the default set of vertices
    this->vertices = new float[this->NUM_VERTICES];
}

PolygonLoader::~PolygonLoader() {
    delete this->vertices;
}

int PolygonLoader::initPolygonLoader() {
    const char *vertexSource = read_shader_from_source("shaders/v1.vert");
    const char *fragmentSource = read_shader_from_source("shaders/f1.frag");
	

    GLuint vaoId = 0;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    std::cout << (char *) gluErrorString(glGetError()) << std::endl;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, this->NUM_VERTICES * sizeof(float), this->vertices, GL_DYNAMIC_DRAW);

    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(0);

    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compile_shader(vertexShader, vertexSource);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compile_shader(fragmentShader, fragmentSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindAttribLocation(shaderProgram, 0, "in_Position");

    glLinkProgram(shaderProgram);

    GLint isLinked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        std::cout << "ERROR linking\n";
    }

    glUseProgram(shaderProgram);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
}

const char* PolygonLoader::read_shader_from_source(std::string filename) {
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

int PolygonLoader::compile_shader(int shader, const char *src) {
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


int PolygonLoader::renderTriangleAt(float x, float y) {

    return 0;
}

int PolygonLoader::renderQuadAt(float x, float y) {
    glClear(GL_COLOR_BUFFER_BIT);
    this->xCoord = x;
    this->yCoord = y;
    this->vertices[0] = this->xCoord - this->scale;
    this->vertices[1] = this->yCoord - this->scale;
    this->vertices[2] = this->xCoord - this->scale;
    this->vertices[3] = this->yCoord + this->scale;
    this->vertices[4] = this->xCoord + this->scale;
    this->vertices[5] = this->yCoord - this->scale;
    this->vertices[6] = this->xCoord + this->scale;
    this->vertices[7] = this->yCoord + this->scale;
    glBufferData(GL_ARRAY_BUFFER, this->NUM_VERTICES * sizeof(float), this->vertices, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    return 0;
}


int PolygonLoader::setCameraCoordinate(float x, float y) {
    this->xCoord = x;
    this->yCoord = y;
    // update the shader here
    return 0;
}

int PolygonLoader::renderQuadAtWorldCoord(float x, float y) {
    // the data that goes into the shader is in terms of world coordinates
    // for now call the renderQuadAt method
    // we'll see if there is a shader to do this later on.
    renderQuadAt(x,y);
    return 0;
}