/**
* @file ShaderProgram.cpp
 * @author mdgr0010
 *
 * @date 04/10/2024
 *
 * @brief Implementación de la clase ShaderProgram
 */

#include <glad/glad.h>
#include <iostream>
#include <string>
#include "ShaderProgram.h"

namespace PAG {

    //Constructor
    PAG::ShaderProgram::ShaderProgram() {
    }

    //Destructor
    ShaderProgram::~ShaderProgram() {
        if(idSP != 0) {
             glDeleteProgram(idSP);
         }
    }

    //Método para crear, compilar y enlazar el shader program
    void ShaderProgram::creaShaderProgram() {
        std::string miVertexShader = vertexShader.getArchivo(nombreShader + "-vs.glsl"); //Obtención del archivo que contiene el código para crear un Vertex Shader
        std::string miFragmentShader = fragmentShader.getArchivo(nombreShader + "-fs.glsl"); //Obtención del archivo que contiene el código para crear un Fragment Shader

        vertexShader.creaShader(GL_VERTEX_SHADER, miVertexShader);//Función que sirve para crear el Vertex Shader
        fragmentShader.creaShader(GL_FRAGMENT_SHADER, miFragmentShader);

        idSP = glCreateProgram(); //Función para crear un programa
        if(idSP == 0) {
            std::cout << "Error creating shader program" << std::endl;
        }
        glAttachShader(idSP, vertexShader.getId()); //Función que une un shader a un programa
        glAttachShader(idSP, fragmentShader.getId()); //Función que une un shader a un programa
        linkShaderProgram(idSP); //Función que se encarga de comprobar que los shaders se hayan unido correctamente y que no haya fallos
    }

    //Función que crea el programa y comprueba que todo funciona correctamente, en caso contrario, muestra el error que ha ocurrido
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
                std::cout << "Cannot create program " << id << std::endl;
                std::cout << logString << std::endl;
            }
        } else {
            std::cout << "Link Shader correcto" << std::endl; //Comprobación
        }
    }

    //Método para utilizar el programa en la aplicación
    void ShaderProgram::useProgram() {
        glUseProgram(idSP);
    }

    /**void ShaderProgram::setNombreShader(std::string nomShader) {
        nombreShader = nomShader;
    }*/

} // PAG