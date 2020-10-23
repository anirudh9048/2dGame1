The goal of this project is to make an app that:
- can draw a line to the screen
- can draw a triangle to the screen
- can draw a rectangle to the screen
- toggle between the three
- uses SDL (?) and OpenGL

Download the SDL2.framework folder and copy it to /Library/Frameworks.
To compile: 
    g++ -framework SDL2 -F./dependencies -framework OpenGL -I ./include/ src/main.cpp -o main
    g++ -std=c++11 -framework SDL2 -F./dependencies -framework OpenGL -I ./include/ src/* -o main

Download the SDL2.framework folder and copy it to /Library/Frameworks

Go to security&privacy in system settings and allow SDL2 to pass (even though the dev is "not verified")

# PolygonLoader
So far, we have a way to load a quadrilateral at any point on the screen in the range [-1f, 1f] for both coordinates.
So we have to specify the opengl coordinates for the render call. Need a way to transition into rendering the world coordinates 
instead. In other words, we need another function that will have a view window based on the current player location and when you
call this function to render a polygon at (x,y), it decides the opengl coordinates for that draw call (again based on the current 
player location). The view matrix will be designed in such a way that the player's current world coordinate is mapped to (0.0f, 0.0f)
in opengl coordinates.

someObj->renderPlayerAt(x, y) : setWorldCoordinate(x,y); renderQuadAt(0,0);

Put the following matrix into a shader:
1 0 -p_x
0 1 -p_y
0 0 1

(p_x, p_y) is the camera position (which also happens to be the player position).

How do we pass in the camera_pos vertex attribute to the shader? https://www.informit.com/articles/article.aspx?p=2429029
