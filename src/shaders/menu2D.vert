#version 330

layout (location = 0) in vec2 position;

uniform vec2 screenSize;

void main() {
    // Convert pixel coordinates (0,0 = top-left) to NDC (-1 to 1, -1 = bottom, 1 = top)
    // X: 0 -> -1, screenWidth -> 1
    // Y: 0 -> 1, screenHeight -> -1 (flip because screen Y is top-down, OpenGL Y is bottom-up)
    vec2 normalizedPos;
    normalizedPos.x = (position.x / screenSize.x) * 2.0 - 1.0;
    normalizedPos.y = 1.0 - (position.y / screenSize.y) * 2.0; // Flip Y: top becomes 1, bottom becomes -1
    gl_Position = vec4(normalizedPos, 0.0, 1.0);
}

