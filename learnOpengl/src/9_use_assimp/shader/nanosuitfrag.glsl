#version 420 core
out vec4 fragcolor;
in vec3 normal;
in vec3 fragpos;
in vec2 texture_coord;

//uniform sampler2D texture_diffuse1;
struct Material {
    sampler2D diffuse; 
    sampler2D specular;
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
struct FlashLight{
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

uniform vec3 viewpos;
vec3 viewDir = normalize(viewpos - fragpos);
vec3 norm = normalize(normal);

void main()
{   
//material.diffuse = texture_diffuse1;
//material.shininess = 32.0;
vec3 result = vec3(0.0);
result += calculate_sunlight(sunlight);
result += calculate_flashlight(flashlight);
for(int i=0; i<4; i++){
    result += calculate_pointlight(light[i]);
}
fragcolor = vec4(result, 1.0);
//fragcolor = vec4(texture(texture_diffuse1, texture_coord).rgb, 1.0);
}

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
        //œﬂ–‘≤Â÷µ
        vec3 result2 = flashdiffuse * _lightstrength * 2.0+ flashspecular * _lightstrength * 1.8;
        float k = (costheta - flashlight.outer_cutoff) / (flashlight.cutoff - flashlight.outer_cutoff);
        return (flashambient *(1-k) + result2 * k) ;
    }
    else{
        vec3 flashambient = flashlight.ambient * texture(material.diffuse, texture_coord).rgb;
        return flashambient;
    }
}