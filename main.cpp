#include <iostream>
//IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "GUI.h"

//Variables globales para el color de fondo
float red = 0.6f;
float green = 0.6f;
float blue = 0.6f;
float incremento = 0.05f; //Paso para incrementar o decrementar el color

//Esta función callback será llamada cuando GLFW produzca algún error
void error_callback (int errNo, const char *desc) {
    std::string aux(desc);
    std::cout << "Error de GLFW número " << errNo << ": " << aux << std::endl;
}

//Esta función callback será llamada cada vez que el área de dibujo
//OpenGL deba ser redibujada
void window_refresh_callback(GLFWwindow* window) {
    PAG::GUI::getInstancia()->refrescar();
    PAG::Renderer::getInstancia()->refrescar();

    glfwSwapBuffers(window);
    std::cout << "Refresh callback called" << std::endl;
}

//Esta función callback será llamada cada vez que se cambie el tamaño
//del área de dibujo OpenGL
void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
    PAG::Renderer::getInstancia()->reedimensionar(width, height);
    std::cout << "Resize callback called" << std::endl;
}

//Esta función callback será llamada cada vez que se pulse una tecla
//dirigida al área de dibujo OpenGL
void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    std::cout << "Key callback called" << std::endl;
}

//Esta función callback será llamada cada vez que se pulse algún botón
//del ratón sobre el área de dibujo OpenGL
void mouse_button_callback (GLFWwindow* window, int button, int action, int mods) {
    if(action == GLFW_PRESS) {
        std::cout << "Pulsado el boton: " << button << std::endl;
    } else {
        if(action == GLFW_RELEASE) {
            std::cout << "Soltado el boton: " << button << std::endl;
        }
    }
}

//Esta función callback será llamada cada vez que se mueva la rueda
//del ratón sobre el área de dibujo OpenGL
void scroll_callback (GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << "Movida la rueda del raton " << xoffset
              << " unidades en horizontal y " << yoffset
              << " unidades en vertical" << std::endl;

    PAG::Renderer::getInstancia()->cambioColor(yoffset, red, green, blue,incremento);
    std::cout << "Color de fondo actualizado: (" << red << ", " << green << ", " << blue << ")" << std::endl;
}

int main() {
    std::cout << "Starting application PAG - Prueba 01" << std::endl;


    //Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback((GLFWerrorfun) error_callback);

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

    //Interrogamos a OpenGL para que nos informe de las propiedades del contexto
    //3D construido
    std::cout << glGetString(GL_RENDERER) << std::endl
              << glGetString(GL_VENDOR) << std::endl
              << glGetString(GL_VERSION) << std::endl
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    //Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback(window, window_refresh_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //Establecemos un gris medio como color con el que se borrará el frame buffer.
    //No tiene por qué ejecutarse en cada paso por el ciclo de eventos
    glClearColor(red, green, blue, 1.0f);

    //Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
    //No tiene por qué ejecutarse en cada paso por el ciclo de eventos
    glEnable(GL_DEPTH_TEST);

    //Ciclo de eventos de la aplicación. La condición de parada es que la
    //ventana principal deba cerrarse. Por ejemplo, si el usuario pulsa el
    //botón de cerrar la ventana (la X)
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //GLFW usa un doble buffer para que no haya parpadeo. Esta orden
        //intercambia el buffer back (en el que se está dibujando) por el
        //que se mostraba hasta ahora (front)
        glfwSwapBuffers(window);

        //Obtiene y organiza los eventos pendientes, tales como pulsaciones de
        //teclas o de ratón, etc. Siempre al final de cada iteración del ciclo
        //de eventos y después de glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //Una vez haya terminado el ciclo de eventos, liberar recursos, etc.
    std::cout << "Finished application PAG - Prueba 01" << std::endl;

    glfwDestroyWindow(window); //Cerramos y destruimosla ventana de la aplicación
    window = NULL;
    glfwTerminate(); //Liberamos los recursos que ocupaba GLFW
}
