# version 420 core
layout(location = 0) in vec3 _gl_position;
layout(location = 1) in vec2 _texture_coord;
layout(location = 2) in vec3 _out_color;
layout(location = 3) in vec3 _normal;
out vec2 texture_coord;
out vec3 out_color;
out vec3 normal;
out vec3 fragpos;
uniform mat4 trans1;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(){
gl_Position =  projection * view * model * trans1 * vec4(_gl_position, 1.0);
texture_coord = _texture_coord;
out_color = _out_color;
normal =  vec3(model * trans1 * vec4(_normal, 1.0) );
fragpos = vec3(model * trans1 * vec4(_gl_position, 1.0) );
}