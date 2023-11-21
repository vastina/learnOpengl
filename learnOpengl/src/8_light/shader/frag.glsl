# version 420 core
out vec4 frag_color;
in vec2 texture_coord;
in vec3 out_color;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightcolor;
void main(){
frag_color = mix(texture(texture1, texture_coord), texture(texture2, texture_coord), 0.2) * vec4(lightcolor,1.0) * vec4(out_color, 1.0) ;
}