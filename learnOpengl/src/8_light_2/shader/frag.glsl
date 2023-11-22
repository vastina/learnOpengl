# version 420 core
out vec4 frag_color;
 
in vec2 texture_coord;
in vec3 normal;
in vec3 fragpos;
uniform sampler2D texture1;
uniform sampler2D texture2;

struct Material {
    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
    float shininess;
};  uniform Material material;
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  uniform Light light;
uniform vec3 viewpos;

void main()
{
vec3 ambient = material.ambient * light.ambient;

vec3 norm = normalize(normal);
vec3 lightDir = normalize(light.position - fragpos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = (diff *material.diffuse) * light.diffuse;
 
vec3 viewDir = normalize(viewpos - fragpos);
vec3 reflectDir = reflect(-lightDir, norm);  
float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
vec3 specular = material.specular * (spec * light.specular);
 
vec4 result = vec4( (ambient + diffuse + specular), 1.0) ;
frag_color =  result ;//mix(texture(texture1, texture_coord), texture(texture2, texture_coord), 0.2) *
}