#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
out vec4 color;

uniform float time;

void main() {
    color = vec4(fragmentColor.r * (sin(fragmentPosition.x * 4.0 + time) + 1.0) * 0.5,
                fragmentColor.g * (sin(fragmentPosition.y * 8.0 + time) + 1.0) * 0.5,
                fragmentColor.b * (sin(fragmentPosition.x * 2.0 + time)  + 1.0) * 0.5, 0.0);
}