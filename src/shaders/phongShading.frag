#version 400

in vec2 texCoord0;
in vec3 normal0;

out vec4 fragColor;

uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform sampler2D diffuse;

void main() {
    vec4 totalLight = vec4(ambientLight, 1.0);
    vec4 textureColor = texture(diffuse, texCoord0);
    vec4 color = vec4(baseColor, 1.0);

    color *= textureColor;

    fragColor = color * totalLight;
}