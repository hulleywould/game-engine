#version 400

in vec2 texCoord0;
out vec4 FragColor;

uniform sampler2D diffuse;

void main() {
    FragColor = texture(diffuse, texCoord0);
}
