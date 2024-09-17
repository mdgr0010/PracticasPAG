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

    //Definimos las características que queremos que tenga el contexto gráfico
    //OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
    //modo Core Profile.
    glfwWindowHint(GLFW_SAMPLES, 4); //Activa antialiasing con 4 muestras.
    //Las siguientes ordenes activan un contexto OpenGL Core Profile 4.1.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    //Definimos el puntero para guardar la dirección de la ventana de la aplicación y
    //la creamos
    GLFWwindow* window;

    //La siguiente línea de código define el tamaño de la ventana, el título, el estado en
    //pantalla y no en pantalla completa y que no comparta recursos con otras ventanas
    window = glfwCreateWindow(1024, 576, "PAG Introduction", NULL, NULL);

    //Comprobamos si la creación de la ventana ha tenido éxito
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //Liberamos los recursos que ocupaba GLFW
        return -2;
    }

    //Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
    //ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent(window);

    //Ahora inicializamos GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window); //Liberamos los recursos que ocupaba GLFW
        window = NULL;
        glfwTerminate();
        return -3;
    }
    return 0;
}
