Need some basic definitions:

#VAO: Vertex Array Object 
An object that contains one or more VBOs and is designed to store the information for an entire rendered object. Ex. a diamond consisting of 4 vertices and a color for each vertex.


#VBO: Vertex Buffer Object
We have been dealing mainly with these. This is a memory buffer (opengl buffer object is an unformatted array) in the high speed memory of your video card designed to hold information about vertices. For example you could have two VBOs, one that describes the coordinates of the veritices and another that describes the color associated with each vertex.

Is there an opengl call to associate a given VAO to its subsidiary VBOs?

https://stackoverflow.com/questions/11821336/what-are-vertex-array-objects

GLuint vaoB[1]; // we will deal with only one of these
glGenVertexArrays(1, vaoB); // create one vertex array object and store the id in vaoB
glBindVertexArray(); ...


https://gamedev.stackexchange.com/questions/8042/whats-the-purpose-of-opengls-vertex-array-objects

https://stackoverflow.com/questions/8704801/glvertexattribpointer-clarification

