#version 330 core
in vec3 colorOut;
out vec4 color2;
void main(){
  color2 = vec4(colorOut, 1.0);
}