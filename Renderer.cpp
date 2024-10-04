/**
 * @file Renderer.cpp
 * @author mdgr0010
 *
 * @date 20/09/2024
 *
 * @brief Implementación de la clase Renderer
 */

#include <glad//glad.h>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Renderer.h"

namespace PAG {
    PAG::Renderer* PAG::Renderer::instancia = nullptr;
    GLfloat PAG::Renderer::vertices[] = { -.5, -.5, 0,
                                           .5, -.5, 0,
                                           .0, .5, 0,};
    GLuint PAG::Renderer::indices[] = { 0, 1, 2,};

    //Constructor por defecto
    Renderer::Renderer() {

    }

    //Destructor
    Renderer::~Renderer() {
        if(idVS != 0) {
            glDeleteShader(idVS);
        }

        if(idFS != 0) {
            glDeleteShader(idFS);
        }

        if(idSP != 0) {
            glDeleteProgram(idSP);
        }

        if(idVBO != 0) {
            glDeleteBuffers(1, &idVBO);
        }

        if(idIBO != 0) {
            glDeleteBuffers(1, &idIBO);
        }

        if(idVAO != 0) {
            glDeleteVertexArrays(1, &idVAO);
        }
    }

    /**
     * Consulta del único objeto de la clase
     * @return La dirección de memoria del objeto
     */
    PAG::Renderer* PAG::Renderer::getInstancia() {
        if (!instancia) {
            instancia = new PAG::Renderer();
        }
        return instancia;
    }

    //Método para hacer el refresco de la escena
    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUseProgram(idSP);
        glBindVertexArray(idVAO);
        glBindBuffer(GL_ARRAY_BUFFER, idIBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }

    //Método para reedimensinar la escena
    void Renderer::reedimensionar(int width, int height) {
        glViewport(0, 0, width, height);
    }

    //Método para cambiar el color de fondo de la escena
    void Renderer::cambioColor(double yoffset, float& red, float& green, float& blue, float incremento) {
        //Modificamos los valores red, blue y green
        //Si se mueve la rueda del ratón hacia arriba, aumentamos los colores
        if(yoffset > 0) {
            red = red + incremento;
            green = green + (incremento * 0.5f); //Incrementamos el verde más lento
            blue = blue + (incremento * 0.3f); //Incrementamos el azul mucho más lento

            //Aseguramos que los valores no incrementan de 1.0f
            if(red > 1.0f) {
                red = 1.0f;
            }
            if(green > 1.0f) {
                green = 1.0f;
            }
            if(blue > 1.0f) {
                blue = 1.0f;
            }
        } else {
            //Si se movemos la rueda del ratón hacia abajo, disminuimos los colores
            red = red - incremento;
            green = green - (incremento * 0.5f); //Incrementamos el verde más lento
            blue = blue - (incremento * 0.3f); //Incrementamos el azul mucho más lento

            //Aseguramos que los valores no desciendan de 0.0f
            if(red < 0.0f) {
                red = 0.0f;
            }
            if(green < 0.0f) {
                green = 0.0f;
            }
            if(blue < 0.0f) {
                blue = 0.0f;
            }
        }

        //Cambiamos el color de fondo
        glClearColor(red, green, blue, 1.0f);
    }

    /**
     * Método para crear, compilar y enlazar el shader program
     * @note No se incluye ninguna comprobación de errores
     */
    void Renderer::creaShaderProgram() {
        std::string miVertexShader =
            "#version 410\n"
            "layout (location = 0) in vec3 position;\n"
            "void main() \n"
            "{ gl_Position = vec4( posicion, 1 );\n"
            "}\n";

        std::string miFragmentShader =
            "#version 410\n"
            "out vec4 colorFragmento;\n"
            "void main() \n"
            "{ colorFragmento = vec4( 1.0, .4, .2, 1.0 );\n"
            "}\n";

        idVS = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* fuenteVS = miVertexShader.c_str();
        glShaderSource(idVS, 1, &fuenteVS, NULL);
        glCompileShader(idVS);

        idFS = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar* fuenteFS = miFragmentShader.c_str();
        glShaderSource(idFS, 1, &fuenteFS, NULL);
        glCompileShader(idFS);

        idSP = glCreateProgram();
        glAttachShader(idSP, idVS);
        glAttachShader(idSP, idFS);
        glLinkProgram(idSP);
    }

    /**
     * Método para crear el VAO para el modelo a renderizar
     * @note No se incluye ninguna comprobación de errores
     */
    void Renderer::creaModelo() {
        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);
        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
        glEnableVertexAttribArray(0);
        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    }

    /**
     * Método para inicializar los parámetros globales de OpenGL
     */
    void Renderer::inicializaOpenGL() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
    }

    /**
     * Método para obtener los archivos necesarios para formar los shaders
     */
    std::string Renderer::getArchivo(std::string archivo) {
        std::ifstream archivoShader;
        archivoShader.open("pag03-" + archivo + "s.glsl");
        if (!archivoShader.is_open()) {
            std::cout << "Error al abrir el archivo" << std::endl;
        }
        std::stringstream streamShader;
        streamShader << archivoShader.rdbuf();
        std::string codigoFuenteShader = streamShader.str();
        archivoShader.close();
        return codigoFuenteShader;
    }

    /**
     * Método que compila los shaders y muestra si existe algún error en el shader elegido
     */
    void Renderer::compilarShader(std::string shader, GLuint id, std::string shaderType) {
        const GLchar* fuente = shader.c_str(); //Se obtiene el código del shader
        glShaderSource(id, 1, &fuente, NULL); //Almacena el código fuente en el identificador del shader
        glCompileShader(id); //Se compila el shader para asegurarnos de que todo está correcto
        GLint compileResult;
        glGetShaderiv(id, GL_COMPILE_STATUS, &compileResult); //Se comprueba que la compilación ha sido correcta
        if (compileResult == GL_FALSE) {
            GLint logLen = 0;
            std::string logString = "";
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
            if (logLen > 0) {
                char* cLogString = new char[logLen];
                GLint written = 0;
                glGetShaderInfoLog(id, logLen, &written, cLogString);
                logString.assign(cLogString);
                delete[] cLogString;
                std::cout << "Cannot compile shader" << shaderType << std::endl;
                std::cout << logString << std::endl;
            }
        } else {
            std::cout << shaderType << " correcto" << std::endl;
        }
    }

} // PAG