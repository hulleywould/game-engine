#version 130

in vec3 vertexPosition;
in vec4 vertexColor;

out vec3 fragmentPosition;
out vec4 fragmentColor;

void    main() {
    gl_Position.xyz = vertexPosition;
    gl_Position.w = 1.0;

    fragmentPosition = vertexPosition;

    fragmentColor = vertexColor;
}

