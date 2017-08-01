#version 400

in vec2 texCoord0;
in vec3 normal0;

out vec4 fragColor;

uniform vec3 color;
uniform sampler2D diffuse;

void main() {
    fragColor = texture(diffuse, texCoord0) * vec4(color, 1.0);
    //fragColor = texture(diffuse, texCoord0) * clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0);
}