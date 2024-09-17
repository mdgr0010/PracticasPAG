#include <iostream>
//IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "Starting application PAG - Prueba 01" << std::endl;

    //Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    if (glfwInit() != GLFW_TRUE) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    return 0;
}
