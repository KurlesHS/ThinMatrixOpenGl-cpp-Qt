#version 400

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;


out vec4 out_Color;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;

void main(void)
{
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);
    float nDotl = dot(unitNormal, unitLightVector);
    float brightness = max(nDotl, 0.2);
    vec3 diffuse = brightness * lightColor;

    // нормализуем вектор камеры
    vec3 unitVectorToCamera = normalize(toCameraVector);
    vec3 lightDirection = -unitLightVector;
    // получаем "отражённый" вектор направления света относительно нормали
    vec3 lightDirectionReflected = reflect(lightDirection, unitNormal);
    // сколько отражённого света попадает в камеру
    float specularFactor = dot(lightDirectionReflected, unitVectorToCamera);
    // отрицательное значенте отржённого света мы не можем получить
    specularFactor = max(specularFactor, 0.0);
    float dampedFactor = pow(specularFactor, shineDamper);
    vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

    out_Color = vec4(diffuse, 1.0) * texture(textureSampler, pass_textureCoords) + vec4(finalSpecular, 1.0);
}
