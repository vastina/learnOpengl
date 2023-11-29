#version 420 core
layout (location = 0) in vec3 _pos;
layout (location = 1) in vec3 _normal;
layout (location = 2) in vec2 _texture_coord;
out vec3 normal;
out vec2 texture_coord;
out vec3 fragpos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
normal =  mat3(transpose(inverse(model) ) ) * _normal ;
texture_coord = _texture_coord;
fragpos = vec3(model * vec4(_pos, 1.0) ); 
gl_Position = projection * view * vec4(fragpos, 1.0);
}