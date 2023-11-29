#version 420 core
out vec4 light_fragcolor;
uniform vec3 _light_fragcolor;
void main()
{
light_fragcolor = vec4(_light_fragcolor, 1.0);
}