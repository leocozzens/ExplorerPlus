#include <iostream>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Check the OpenGL version
    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    if (version) std::cout << "OpenGL version: " << version << std::endl;
    else std::cerr << "Failed to retrieve OpenGL version" << std::endl;

    // Clean up and exit
    glfwTerminate();
    return 0;
}