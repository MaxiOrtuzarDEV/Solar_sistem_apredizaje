#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

float heigthScreen = 600.0f;
float widthScreen = 800.0f;

GLFWwindow* startGlfw();
void cargandoOpengl(GLFWwindow* window);

int main() {
    GLFWwindow* window = startGlfw();

    while (!glfwWindowShouldClose(window)) {



        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

GLFWwindow* startGlfw() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }
    GLFWwindow* window = glfwCreateWindow(static_cast<int>(widthScreen), static_cast<int>(heigthScreen), "Hello World", nullptr, nullptr);

    cargandoOpengl(window);


    return window;
}

void cargandoOpengl(GLFWwindow* window) {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glViewport(0, 0, static_cast<int>(widthScreen), static_cast<int>(heigthScreen));

}