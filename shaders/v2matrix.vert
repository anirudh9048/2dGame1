#version 330 core

in vec2 world_pos;
in vec2 camera_pos;

void main() 
{
  vec3 world_pos_hmg = vec3(world_pos, 1);
  mat3 transform_mat = mat3(
      1, 0, 0,
      0, 1, 0,
      -camera_pos.x, -camera_pos.y, 1
  );  
  vec3 op_gl_coord = transform_mat * world_pos_hmg;
  gl_Position = vec4(op_gl_coord, 1.0);
}