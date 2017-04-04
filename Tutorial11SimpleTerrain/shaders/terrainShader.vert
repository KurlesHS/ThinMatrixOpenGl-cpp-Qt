#version 400 core

in vec3 position;
in vec3 normal;
in vec2 textureCoords;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

void main(void)
{
    vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
    pass_textureCoords = textureCoords * 40.;

    // крутим нормаль так же, как и объект
    vec4 vec4SurfaceNormal = transformationMatrix * vec4(normal, 0.0);
    surfaceNormal = vec4SurfaceNormal.xyz;
    toLightVector = lightPosition - worldPosition.xyz;
    // магия - из матрицы viewMatrix получаем точку, где она находиться
    vec3 cameraPosition = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    // вектор направления, куда смотрит камера
    toCameraVector = cameraPosition - worldPosition.xyz;
}
