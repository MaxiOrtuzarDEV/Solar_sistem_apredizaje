#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Objeto.h"
#include "src/shader/Shader.h"
#include <cmath>
#include <iostream>
#include <cmath>


float heigthScreen = 600.0f;
float widthScreen = 800.0f;

GLFWwindow* startGlfw();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLuint compileShader();
std::vector<float> generaCIRCLE(float radius, int segments);


std::vector<float> triaguloVertex= {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

int main() {
    GLFWwindow* window = startGlfw();
    if (!window) {
        return -1;
    }

    glViewport(0,0, static_cast<int>(widthScreen), static_cast<int>(heigthScreen));

    const GLuint shaderProgram = compileShader();
    Objeto triangulo(triaguloVertex, shaderProgram);
    Objeto circulo(generaCIRCLE(0.3f, 100), shaderProgram);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.10f, 0.19f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //triangulo.dibujar();
        circulo.dibujar();
        circulo.updateBlueComponentColor((std::sin(static_cast<float>(glfwGetTime())) / 2.0f) + 0.5f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

GLFWwindow* startGlfw() {

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(static_cast<int>(widthScreen), static_cast<int>(heigthScreen), "Hello World", nullptr, nullptr);

    if (!window) {
        std::cout << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    return window;
}

void framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

GLuint compileShader() {

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::vector<float> generaCIRCLE(float radius, const int segments) {
    std::vector<float> vertices;

    // Centro del círculo
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f); // z

    // Borde del círculo
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * M_PI * i / segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }

    return vertices;
}
