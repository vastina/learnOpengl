# version 420 core
out vec4 frag_color;

in vec2 texture_coord;
in vec3 normal;
in vec3 fragpos;

struct Material {
    sampler2D diffuse; 
    sampler2D specular;
    sampler2D emission;
    float shininess;
};  uniform Material material;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  uniform PointLight light[4];
struct sunLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  uniform sunLight sunlight;
struct FlashLight{//手电筒
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction; vec3 position;
    float cutoff, outer_cutoff;
};  uniform FlashLight flashlight;
struct LightStrength{
    float constant;
    float linear;
    float quadratic;
};  uniform LightStrength lightstrength;

vec3 calculate_sunlight(sunLight sunlight);
vec3 calculate_pointlight(PointLight light);
vec3 calculate_flashlight(FlashLight flashlight);

uniform float move; uniform float t;//just for fun
uniform vec3 viewpos;
vec3 viewDir = normalize(viewpos - fragpos);
vec3 norm = normalize(normal);

void main()
{
vec3 result = vec3(0.0);
result += calculate_sunlight(sunlight);
result += calculate_flashlight(flashlight);
for(int i=0; i<4; i++){
    result += calculate_pointlight(light[i]);
}
vec3 emission =  texture(material.emission,vec2(texture_coord.x, texture_coord.y + move)).rgb * vec3(0.2) *(0.75 + 0.5*sin(t) );
frag_color =  vec4 (result+emission , 1.0) ;

}
//话说这玩意能传函数指针进去吗，能写lambda吗，这应该是cpp吧。。。。。。
vec3 calculate_pointlight(PointLight light){
    float distance = length(light.position - fragpos);
    float _lightstrength = 1.0 / (lightstrength.constant + lightstrength.linear*distance + lightstrength.quadratic*pow(distance, 2) );
    vec3 lightDir = normalize(light.position - fragpos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 ambient = vec3( texture(material.diffuse, texture_coord) ) * light.ambient * _lightstrength;
    vec3 diffuse = vec3( texture(material.diffuse, texture_coord) ) * diff * light.diffuse * _lightstrength;
    vec3 specular = vec3( texture(material.specular, texture_coord) ) * spec * light.specular * _lightstrength;
    return (ambient + diffuse + specular);
}

vec3 calculate_sunlight(sunLight sunlight){
    vec3 sunlightDir = normalize(-sunlight.direction);
    float sundiff = max(dot(norm, sunlightDir), 0.0);
    vec3 sunReflectDir = reflect(-sunlightDir, norm);
    float sunspec = pow(max(dot(viewDir, sunReflectDir), 0.0), material.shininess);
    vec3 ambient = vec3( texture(material.diffuse, texture_coord) ) * sunlight.ambient ;
    vec3 diffuse = vec3( texture(material.diffuse, texture_coord) ) * sundiff * sunlight.diffuse ;
    vec3 specular = vec3( texture(material.specular, texture_coord) ) * sunspec * sunlight.specular ;
    return (ambient + diffuse + specular);
}

vec3 calculate_flashlight(FlashLight flashlight){
    vec3 flashlightDir = normalize(flashlight.position - fragpos);
    float costheta = dot(normalize(flashlight.position - fragpos), normalize(-flashlight.direction) );
    if(costheta > flashlight.cutoff) {    
        // diffuse 
        float flashdiff = max(dot(norm, flashlightDir), 0.0);
        vec3 flashdiffuse = flashlight.diffuse * flashdiff * texture(material.diffuse, texture_coord).rgb;  
        // specular
        vec3 flashReflectDir = reflect(-flashlightDir, norm);  
        float flashspec = pow(max(dot(viewDir, flashReflectDir), 0.0), material.shininess);
        vec3 flashspecular = flashlight.specular * flashspec *  vec3(texture(material.specular, texture_coord) ) ;  
        // attenuation
        float distance = length(flashlight.position - fragpos);
        float _lightstrength = 1.0 / (lightstrength.constant + lightstrength.linear*distance + lightstrength.quadratic*pow(distance, 2) );    

        flashdiffuse  *= _lightstrength * 2.0;
        flashspecular *= _lightstrength * 3.0;      
        return (flashdiffuse + flashspecular) ;
    }
    else if(costheta > flashlight.outer_cutoff){
        vec3 flashambient = flashlight.ambient * texture(material.diffuse, texture_coord).rgb;
        float flashdiff = max(dot(norm, flashlightDir), 0.0);
        vec3 flashdiffuse = flashlight.diffuse * flashdiff * texture(material.diffuse, texture_coord).rgb;  
        vec3 flashReflectDir = reflect(-flashlightDir, norm);  
        float flashspec = pow(max(dot(viewDir, flashReflectDir), 0.0), material.shininess);
        vec3 flashspecular = flashlight.specular * flashspec *  vec3(texture(material.specular, texture_coord) ) ;  
        float distance = length(flashlight.position - fragpos);
        float _lightstrength = 1.0 / (lightstrength.constant + lightstrength.linear*distance + lightstrength.quadratic*pow(distance, 2) ); 
        //线性插值
        vec3 result2 = flashdiffuse * _lightstrength * 2.0+ flashspecular * _lightstrength * 1.8;
        float k = (costheta - flashlight.outer_cutoff) / (flashlight.cutoff - flashlight.outer_cutoff);
        return (flashambient *(1-k) + result2 * k) ;
    }
    else{
        vec3 flashambient = flashlight.ambient * texture(material.diffuse, texture_coord).rgb;
        return flashambient;
    }
}