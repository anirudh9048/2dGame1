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
	
    // ----- DON'T NEED ------
    // GLuint vaoId = 0;
    // glGenVertexArrays(1, &vaoId);
    // glBindVertexArray(vaoId);

    // std::cout << (char *) gluErrorString(glGetError()) << std::endl;

    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glEnableVertexAttribArray(0);

    // glBufferData(GL_ARRAY_BUFFER, this->NUM_VERTICES * sizeof(float), this->vertices, GL_DYNAMIC_DRAW);

    
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    // ------------------------
    
    
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
// DEPRECATED : use renderQuadAtWorldCoord instead
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
    glBindVertexArray(q.vao_id);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    return 0;
}

// this function name is a bit of a misnomer
// this should really be adding a new vertex buffer (along with new VAO) ???
// it really should be called add vertex buffer to quad
void PolygonLoader::addQuadToVertexBuffer(PolygonLoader::quad_t& quad) {
    GLuint vao_new = 1; //the initialization really shouldn't matter; double check this
    glGenVertexArrays(1, &vao_new);
    glBindVertexArray(vao_new);

    GLuint vbo_new;
    glGenBuffers(1, &vbo_new);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_new);

    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), quad.heap_vertex_data, GL_DYNAMIC_DRAW);

    // defining an array of generic vertex data
    // index :  index of generic vertex attr to be modified 0 -> world pos, 1 -> camera coordinate
    // size : # of components per vertex attr
    // type
    // normalized : 
    // stride : 0 --> tightly packed byte offset between values
    // pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

    quad.vao_id = vao_new;
    quad.vbo_id = vbo_new;

    return;
}

int PolygonLoader::addQuadAt(float x, float y, float width, float height) {
    int new_idx = this->quads.size();
    quad_t new_quad;
    new_quad.quad_id = new_idx;
    new_quad.center_x = x;
    new_quad.center_y = y;
    new_quad.width = width;
    new_quad.height = height;
    new_quad.vertices[0].x = x - width / 2;
    new_quad.vertices[0].y = y - height / 2;
    new_quad.vertices[1].x = x - width / 2;
    new_quad.vertices[1].y = y + height / 2;
    new_quad.vertices[2].x = x + width / 2;
    new_quad.vertices[2].y = y - height / 2;
    new_quad.vertices[3].x = x + width / 2;
    new_quad.vertices[3].y = y + height / 2;
    new_quad.heap_vertex_data = new float[8]; //todo replace with constant
    int index = 0;
    for (int i = 0; i < 4; i++) {
        new_quad.heap_vertex_data[index++] = new_quad.vertices[i].x;
        new_quad.heap_vertex_data[index++] = new_quad.vertices[i].y;
    }
    printFloatArr(new_quad.heap_vertex_data, 8);
    this->addQuadToVertexBuffer(new_quad);
    this->quads.push_back(new_quad);
    return new_idx;
}

int PolygonLoader::moveQuadTo(int quad_id, float x, float y) {
    LOG("Move quad " + std::to_string(quad_id) + " to " + std::to_string(x) + " " + std::to_string(y));
    quad_t& quad = this->quads[quad_id];
    quad.center_x = x;
    quad.center_y = y;
    LOG("Binding vao with id " + std::to_string(quad.vao_id));
    glBindVertexArray(quad.vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, quad.vbo_id);
    quad.vertices[0].x = x - quad.width / 2;
    quad.vertices[0].y = y - quad.height / 2;
    quad.vertices[1].x = x - quad.width / 2;
    quad.vertices[1].y = y + quad.height / 2;
    quad.vertices[2].x = x + quad.width / 2;
    quad.vertices[2].y = y - quad.height / 2;
    quad.vertices[3].x = x + quad.width / 2;
    quad.vertices[3].y = y + quad.height / 2;
    int index = 0;
    for (int i = 0; i < 4; i++) {
        quad.heap_vertex_data[index++] = quad.vertices[i].x;
        quad.heap_vertex_data[index++] = quad.vertices[i].y;
    }
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), quad.heap_vertex_data, GL_DYNAMIC_DRAW);
    glBindVertexArray(0);
}

std::pair<float, float> PolygonLoader::getQuadCoordinates(int quad_id) {
    quad_t quad = this->quads[quad_id];
    std::pair<float, float> ret = std::make_pair(quad.center_x, quad.center_y);
    return ret;
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


void PolygonLoader::setLineVertexBuffers(PolygonLoader::line_t& _line) {
    GLuint vao_id = 1;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    GLuint vbo_id = 1;
    glGenBuffers(1, &vbo_id);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, _line.heap_point_data, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    _line.vaoid = vao_id;
    _line.vboid = vbo_id;
    glBindVertexArray(0);
    
}

int PolygonLoader::renderLineAtWorldCoord(int line_id) {
    line_t l = this->lines[line_id];
    glBindVertexArray(l.vaoid);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}

int PolygonLoader::addLineAt(float x1, float y1, float x2, float y2) {
    int line_id = this->lines.size();
    line_t new_line;
    new_line.p1 = point_t{x1,y1};
    new_line.p2 = point_t{x2,y2};
    new_line.line_id = line_id;
    new_line.heap_point_data = new float[4];
    new_line.heap_point_data[0] = x1;
    new_line.heap_point_data[1] = y1;
    new_line.heap_point_data[2] = x2;
    new_line.heap_point_data[3] = y2;
    this->setLineVertexBuffers(new_line);
    this->lines.push_back(new_line);
    return line_id;
}

int PolygonLoader::moveLineTo(int line_id, float x1, float y1, float x2, float y2) {}

std::pair<float, float> PolygonLoader::getLineCoordinates(int line_id) {}