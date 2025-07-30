
#ifndef SHADER_H
#define SHADER_H

const char* vertexShaderSource = R"glsl(
    #version 330 core

    layout(location = 0) in vec3 aPos; // Posición del vértice

    void main()
    {
        gl_Position = vec4(aPos, 1.0); // Transformación directa
    }
)glsl";

const char* fragmentShaderSource = R"glsl(
    #version 330 core

    out vec4 FragColor;

    uniform vec4 ourColor; // Color recibido desde el programa en C++

    void main()
    {
        FragColor = ourColor; // Usa el color enviado desde C++
    }
)glsl";

#endif //SHADER_H
