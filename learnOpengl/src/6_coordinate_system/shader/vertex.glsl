# version 420 core
layout(location = 0) in vec3 _gl_position;
layout(location = 1) in vec2 _texture_coord;
out vec2 texture_coord;
uniform mat4 trans1;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(){
gl_Position = projection * view * model * trans1 * vec4(_gl_position, 1.0);
texture_coord = _texture_coord;
}