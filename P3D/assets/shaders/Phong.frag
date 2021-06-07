#version 440 core

out vec4 FragColor;

in V2F
{
    vec3 normal;
    vec2 textCoord;
    vec3 fragPos;
} v2f;

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
struct AmbientLight
{
    vec3 Color;
};

struct DirectionalLight
{
    vec3 Direction;
    vec3 Color;
};

struct PointLight
{
    vec3 Position;

    vec3 Color;

    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLight
{
    vec3 Position;
    vec3 Direction;
    
    vec3 Color;
    
    float InnerCutOff;
    float OuterCutOff;
};

uniform struct Lighting
{
    bool AmbientEnable;
    bool DirectionalEnable;
    bool PointEnable;
    bool SpotEnable;
    
    AmbientLight Ambient;
    DirectionalLight Directional;
    PointLight Point;
    SpotLight Spot;
} u_Lighting;

uniform vec3 u_CameraPos;

vec4 CalculateDirectionLight();
vec4 CalculatePointLight();
vec4 CalculateSpotLight();

void main()
{
    // If a texture has given use sample from texture, if not use a neutral value (white)
    vec4 diffuseSample = u_Material.HasDiffuseMap ? texture(u_Material.DiffuseMap, v2f.textCoord) : vec4(1.0);
    
    // Diffuse color
    vec4 diffuseColor = diffuseSample * vec4(u_Material.DiffuseColor, 1.0f);
    
    // Emissive color, if a texture was given use sample from texture, if not use emissive color
    vec4 emissiveSample = u_Material.HasEmissiveMap ? texture(u_Material.EmissiveMap, v2f.textCoord) : vec4(u_Material.EmissiveColor, 1.0f);
    
    vec4 light = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Ambient light
    if (u_Lighting.AmbientEnable)
        light += vec4(u_Lighting.Ambient.Color, 1.0f);
    
    // Directional light
    if (u_Lighting.DirectionalEnable)
        light += CalculateDirectionLight();
    
    // Point light
    if (u_Lighting.PointEnable)
        light += CalculatePointLight();
    
    // Spot light
    if (u_Lighting.SpotEnable)
        light += CalculateSpotLight();
    
    FragColor = light * diffuseColor + emissiveSample;
}

vec4 CalculateDirectionLight()
{
    DirectionalLight light = u_Lighting.Directional;
    
    vec3 lightDir = normalize(-light.Direction);

    float diff = max(dot(v2f.normal, lightDir), 0.0f);
    vec4 diffuse = vec4(diff * light.Color, 1.0f);

    vec3 viewDir = normalize(u_CameraPos - v2f.fragPos);
    vec3 reflectionDir = reflect(-lightDir, v2f.normal);

    float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), u_Material.SpecularExponent);
    vec4 specular = vec4(spec * u_Material.SpecularColor, 1.0f);
    
    return diffuse + specular;
}

vec4 CalculatePointLight()
{
    PointLight light = u_Lighting.Point;
    
    vec3 lightDir = normalize(light.Position - v2f.fragPos);

    float diff = max(dot(v2f.normal, lightDir), 0.0f);
    vec4 diffuse = vec4(diff * light.Color, 1.0f);
    
    vec3 viewDir = normalize(u_CameraPos - v2f.fragPos);
    vec3 reflectionDir = reflect(-lightDir, v2f.normal);

    float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), u_Material.SpecularExponent);
    vec4 specular = vec4(spec * u_Material.SpecularColor, 1.0f);

    float distance = length(light.Position - v2f.fragPos);
    float attenuation = 1.0f / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

    return (diffuse + specular) * attenuation;
}

vec4 CalculateSpotLight()
{
    SpotLight light = u_Lighting.Spot;
    
    vec3 lightDir = normalize(light.Position - v2f.fragPos);

    float diff = max(dot(v2f.normal, lightDir), 0.0f);
    vec4 diffuse = vec4(diff * light.Color, 1.0f);

    vec3 viewDir = normalize(u_CameraPos - v2f.fragPos);
    vec3 reflectionDir = reflect(-lightDir, v2f.normal);

    float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), u_Material.SpecularExponent);
    vec4 specular = vec4(spec * u_Material.SpecularColor, 1.0f);
    
    float theta = dot(lightDir, normalize(-light.Direction));
    float epsilon = light.InnerCutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0f, 1.0f);
    
    return (diffuse + specular) * intensity;
}
