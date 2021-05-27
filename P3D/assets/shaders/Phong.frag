#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec2 textCoord;
in vec3 fragPos;

/* Material properties */
uniform struct Material
{
    bool HasDiffuseMap;
    bool HasEmissiveMap;
    
    sampler2D DiffuseMap;
    vec3 DiffuseColor;
    
    sampler2D EmissiveMap;
    vec3 EmissiveColor;

    vec3 SpecularColor;
    float SpecularExponent;
} u_Material;

/* Lighting */
uniform vec3 u_AmbientColor;

uniform vec3 u_DirectionalLightPosition;
uniform vec3 u_DirectionalLightColor;

uniform vec3 u_CameraPos;

void main()
{
    // If a texture has given use sample from texture, if not use a neutral value (white)
    vec4 diffuseSample = u_Material.HasDiffuseMap ? texture(u_Material.DiffuseMap, textCoord) : vec4(1.0);
    
    // Diffuse color
    vec4 diffuseColor = diffuseSample * vec4(u_Material.DiffuseColor, 1.0f);
    
    // Emissive color, if a texture was given use sample from texture, if not use emissive color
    vec4 emissiveSample = u_Material.HasEmissiveMap ? texture(u_Material.EmissiveMap, textCoord) : vec4(u_Material.EmissiveColor, 1.0f);
    
    // Ambient light
    vec4 ambientLight = vec4(u_AmbientColor, 1.0f);
    
    // Directional light(s)
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_DirectionalLightPosition - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0f);
    vec4 directionalLight = vec4(diff * u_DirectionalLightColor, 1.0f);
    
    // Specular
    vec3 viewDir = normalize(u_CameraPos - fragPos);
    vec3 reflectionDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), u_Material.SpecularExponent);
    vec4 specular = vec4(spec * u_Material.SpecularColor, 1.0f);

    FragColor = (ambientLight + directionalLight + specular) * diffuseColor;
    //FragColor = diffuseSample;
    //FragColor = emissiveSample;
}
