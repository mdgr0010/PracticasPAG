/**
* @file ShaderProgram.cpp
 * @author mdgr0010
 *
 * @date 04/10/2024
 *
 * @brief Implementación de la clase ShaderProgram
 */

#include <glad//glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include "ShaderProgram.h"

namespace PAG {
    PAG::ShaderProgram::ShaderProgram() {
    }

    ShaderProgram::~ShaderProgram() {
         if(idVS != 0) {
             glDeleteShader(idVS);
         }

         if(idFS != 0) {
             glDeleteShader(idFS);
         }

         if(idSP != 0) {
             glDeleteProgram(idSP);
         }
    }

    /**
     * Método para crear, compilar y enlazar el shader program
     */
    void ShaderProgram::creaShaderProgram() {
        std::string miVertexShader = getArchivo("v"); //Obtención del archivo que contiene el código para crear un Vertex Shader
        std::string miFragmentShader = getArchivo("f"); //Obtención del archivo que contiene el código para crear un Fragment Shader

        idVS = glCreateShader(GL_VERTEX_SHADER); //Función que sirve para crear el Vertex Shader
        if(idVS == 0) {
            std::cout << "Error creating vertex shader" << std::endl;
        } else {
            compilarShader(miVertexShader, idVS, "VertexShader"); //Función que compila el archivo que contiene el código fuente del shader y que lo une a un id
        }

        idFS = glCreateShader(GL_FRAGMENT_SHADER);
        if(idFS == 0) {
            std::cout << "Error creating fragment shader" << std::endl;
        } else {
            compilarShader(miFragmentShader, idFS, "FragmentShader"); //Función que compila el archivo que contiene el código fuente del shader y que lo une a un id
        }

        idSP = glCreateProgram(); //Función para crear un programa
        if(idSP == 0) {
            std::cout << "Error creating shader program" << std::endl;
        }
        glAttachShader(idSP, idVS); //Función que une un shader a un programa
        glAttachShader(idSP, idFS); //Función que une un shader a un programa
        linkShaderProgram(idSP); //Función que se encarga de comprobar que los shaders se hayan unido correctamente y que no haya fallos
    }

     /**
     * Método para obtener los archivos necesarios para formar los shaders
     */
    std::string ShaderProgram::getArchivo(std::string archivo) {
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
    void ShaderProgram::compilarShader(std::string shader, GLuint id, std::string shaderType) {
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

    /**
     * Función que crea el programa y comprueba que todo funciona correctamente, en caso contrario, muestra el error que ha ocurrido
     */
    void ShaderProgram::linkShaderProgram(GLuint id) {
        glLinkProgram(id);
        GLint linkSuccess = 0;
        glGetProgramiv(id, GL_LINK_STATUS, &linkSuccess); //Función que comprueba que todo funciona correctamente
        if (linkSuccess == GL_FALSE) { //En caso de que haya algún error, se vuelve a comprobar para guardar el mensaje de error y poder mostrarlo por pantalla
            GLint logLen = 0;
            std::string logString = "";
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLen);
            if (logLen > 0) {
                char* cLogString = new char[logLen];
                GLint written = 0;
                glGetProgramInfoLog(id, logLen, &written, cLogString);
                logString.assign(cLogString);
                delete[] cLogString;
                std::cout << "Cannot create program" << id << std::endl;
                std::cout << logString << std::endl;
            }
        } else {
            std::cout << "Link Shader correcto" << std::endl; //Comprobación
        }
    }

    /**
     * Método para utilizar el programa en la aplicación
     */
    void ShaderProgram::useProgram() {
        glUseProgram(idSP);
    }

} // PAG