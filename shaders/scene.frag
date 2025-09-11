#version 460 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D diffuse0;
uniform int numLights;

uniform sampler2D shadowAtlas; // depth texture atlas
uniform int tilesPerSide;      // e.g., 4 means 4x4 tiles

struct Light {
    vec4 position;
    vec4 color;
    vec4 direction;
    mat4 shadowMatrices[2];
};

layout(std430, binding = 0) buffer LightBlock {
    Light lights[];
};

float samplePointShadow(mat4 lightMatrix, vec3 fragPos, int tileIndex) {
    // Project fragment position to light space
    vec4 fragPosLight = lightMatrix * vec4(fragPos, 1.0);
    
    // Convert from clip space to [0,1] UV
    vec3 projCoords = fragPosLight.xyz / fragPosLight.w * 0.5 + 0.5;
    
    // Compute tile offset in atlas
    int row = tileIndex / tilesPerSide;
    int col = tileIndex % tilesPerSide;
    vec2 tileOffset = vec2(col, row) / float(tilesPerSide);
    vec2 tileScale  = vec2(1.0 / float(tilesPerSide));

    vec2 uv = projCoords.xy * tileScale + tileOffset;

    float closestDepth = texture(shadowAtlas, uv).r;
    float currentDepth = projCoords.z;

    // simple shadow bias
    float bias = 0.005;
    return currentDepth - bias > closestDepth ? 0.0 : 1.0;
}

void main() {
    vec3 texColor = texture(diffuse0, TexCoord).rgb;
    vec3 norm = normalize(Normal);
    vec3 finalColor = vec3(0.2);

    for (int i = 0; i < numLights; i++) {
        vec3 lightColor = lights[i].color.rgb * lights[i].color.a;
        float diff = 0.0;

        if (lights[i].position.w == 0.0) {
            // Directional
            vec3 lightDir = normalize(-lights[i].direction.xyz);
            diff = max(dot(norm, lightDir), 0.0);
        } 
        else if (lights[i].position.w == 1.0) {
            // // Point
            // vec3 lightDir = normalize(lights[i].position.xyz - FragPos);
            // float distance = length(lights[i].position.xyz - FragPos);
            // float attenuation = 1.0 / (distance * distance);
            // diff = max(dot(norm, lightDir), 0.0) * attenuation;

            vec3 lightDir = normalize(lights[i].position.xyz - FragPos);
            float distance = length(lights[i].position.xyz - FragPos);
            float attenuation = 1.0 / (distance * distance);
            diff = max(dot(norm, lightDir), 0.0) * attenuation;

            // Shadow factor (0 = in shadow, 1 = lit)
            int tileIndex = i * 2; // +Z matrix in atlas
            float shadow = samplePointShadow(lights[i].shadowMatrices[0], FragPos, tileIndex);

            diff *= shadow;
        } 
        else if (lights[i].position.w == 2.0) {
            // Spot
            vec3 lightDir = normalize(lights[i].position.xyz - FragPos);
            float theta = dot(lightDir, normalize(-lights[i].direction.xyz));
            if (theta > lights[i].direction.w) {
                float distance = length(lights[i].position.xyz - FragPos);
                float attenuation = 1.0 / (distance * distance);
                diff = max(dot(norm, lightDir), 0.0) * attenuation;
            }
        }

        finalColor += lightColor * diff;
    }

    FragColor = vec4(texColor * finalColor, 1.0);
}