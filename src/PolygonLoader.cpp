#include "PolygonLoader.h"

PolygonLoader::PolygonLoader() {
    // these are the default set of vertices
    this->vertices = new float[this->NUM_VERTICES];
}

PolygonLoader::~PolygonLoader() {
    delete this->vertices;
}

int PolygonLoader::initPolygonLoader() {
    const char *vertexSource = read_shader_from_source("shaders/v2matrix.vert");
    const char *fragmentSource = read_shader_from_source("shaders/f1.frag");
	

    GLuint vaoId = 0;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    std::cout << (char *) gluErrorString(glGetError()) << std::endl;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);

    glBufferData(GL_ARRAY_BUFFER, this->NUM_VERTICES * sizeof(float), this->vertices, GL_DYNAMIC_DRAW);

    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compile_shader(vertexShader, vertexSource);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compile_shader(fragmentShader, fragmentSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindAttribLocation(shaderProgram, 0, "world_pos");
    glBindAttribLocation(shaderProgram, 1, "camera_pos");

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

// Render at world coordinate
int PolygonLoader::renderQuadAt(float x, float y) {
    glClear(GL_COLOR_BUFFER_BIT);
    this->vertices[0] = x - this->scale;
    this->vertices[1] = y - this->scale;
    this->vertices[2] = x - this->scale;
    this->vertices[3] = y + this->scale;
    this->vertices[4] = x + this->scale;
    this->vertices[5] = y - this->scale;
    this->vertices[6] = x + this->scale;
    this->vertices[7] = y + this->scale;
    glBufferData(GL_ARRAY_BUFFER, this->NUM_VERTICES * sizeof(float), this->vertices, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    return 0;
}


int PolygonLoader::setCameraCoordinate(float x, float y) {
    this->camera_x = x;
    this->camera_y = y;
    // update the shader here
    float arr[2] = {x, y};
    glVertexAttrib2fv(1, arr);
    return 0;
}

int PolygonLoader::renderQuadAtWorldCoord(int quad_id) {
    // the data that goes into the shader is in terms of world coordinates
    // for now call the renderQuadAt method
    // we'll see if there is a shader to do this later on.
    // first get the vao to bind 
    quad_t q = this->quads[quad_id];
    LOG("Binding " + std::to_string(quad_id));
    glBindVertexArray(q.vao_id);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    return 0;
}

// this function is a bit of a misnomer
// this should really be adding a new vertex buffer (along with new VAO) ???
int PolygonLoader::addQuadToVertexBuffer(PolygonLoader::quad_t quad) {
    GLuint vao_new = 1; //the initialization really shouldn't matter; double check this
    glGenVertexArrays(1, &vao_new);
    glBindVertexArray(vao_new);

    GLuint vbo_new;
    glGenBuffers(1, &vbo_new);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_new);

    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), quad.heap_vertex_data, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    return vao_new;
}

int PolygonLoader::addQuadAt(float x, float y) {
    int new_idx = this->quads.size();
    quad_t new_quad;
    new_quad.quad_id = new_idx;
    new_quad.vertices[0].x = x - this->scale;
    new_quad.vertices[0].y = y - this->scale;
    new_quad.vertices[1].x = x - this->scale;
    new_quad.vertices[1].y = y + this->scale;
    new_quad.vertices[2].x = x + this->scale;
    new_quad.vertices[2].y = y - this->scale;
    new_quad.vertices[3].x = x + this->scale;
    new_quad.vertices[3].y = y + this->scale;
    new_quad.heap_vertex_data = new float[8]; //todo replace with constant
    int index = 0;
    for (int i = 0; i < 4; i++) {
        new_quad.heap_vertex_data[index++] = new_quad.vertices[i].x;
        new_quad.heap_vertex_data[index++] = new_quad.vertices[i].y;
    }
    printFloatArr(new_quad.heap_vertex_data, 8);
    int n_vao = this->addQuadToVertexBuffer(new_quad);
    new_quad.vao_id = n_vao;
    this->quads.push_back(new_quad);
    return new_idx;
}

int PolygonLoader::moveQuadTo(int quad_id, float x, float y) {
    LOG("Move quad " + std::to_string(quad_id) + " to " + std::to_string(x) + " " + std::to_string(y) + "\n");
    quad_t quad = this->quads[quad_id];
    glBindVertexArray(quad.vao_id);
    quad.vertices[0].x = x - this->scale;
    quad.vertices[0].y = y - this->scale;
    quad.vertices[1].x = x - this->scale;
    quad.vertices[1].y = y + this->scale;
    quad.vertices[2].x = x + this->scale;
    quad.vertices[2].y = y - this->scale;
    quad.vertices[3].x = x + this->scale;
    quad.vertices[3].y = y + this->scale;
    int index = 0;
    for (int i = 0; i < 4; i++) {
        quad.heap_vertex_data[index++] = quad.vertices[i].x;
        quad.heap_vertex_data[index++] = quad.vertices[i].y;
    }
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), quad.heap_vertex_data, GL_DYNAMIC_DRAW);
}

void PolygonLoader::printQuad(quad_t quad) {
    std::string str = std::to_string(quad.quad_id) + ": \n";
    for (quad_vertex_t q : quad.vertices) {
        str += std::to_string(q.x) + "," + std::to_string(q.y);
        str += "\n";
    }
    LOG(str);
}

 void PolygonLoader::printFloatArr(float f[], int size) {
    std::string s = ""; 
    for (int i = 0; i < size; i++) {
        s += std::to_string(f[i]) + ", ";
    }
    LOG(s);
 }