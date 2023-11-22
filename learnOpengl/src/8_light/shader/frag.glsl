# version 420 core
out vec4 frag_color;
in vec2 texture_coord;
in vec3 out_color;
in vec3 normal;
in vec3 fragpos;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float ambientStrength ;
uniform float specularStrength = 0.3 ;
uniform vec3 lightpos = vec3(5.0, 5.0, 5.0); 
uniform vec4 light_fragcolor = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 viewpos;
vec3 norm;	vec3 lightDir;  vec3 viewDir;	vec3 reflectDir;	vec3 specular;
void main()
{
norm = normalize(normal);
lightDir = normalize(lightpos - fragpos);
float diff = max(dot(norm, lightDir), 0.0);
viewDir = normalize(viewpos - fragpos);
reflectDir = reflect(-lightDir, norm);  
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec4 result = (1.0*diff + ambientStrength+ specularStrength * spec) * light_fragcolor;
frag_color = mix(texture(texture1, texture_coord), texture(texture2, texture_coord), 0.2) * result * vec4(out_color, 1.0);
}