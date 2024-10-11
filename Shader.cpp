/**
* @file Shader.cpp
 * @author mdgr0010
 *
 * @date 04/10/2024
 *
 * @brief Implementación de la clase Shader
 */

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include "Shader.h"

namespace PAG {
     //Constructor
     Shader::Shader() {
     }

     //Destructor
     Shader::~Shader() {
         if(id != 0) {
             glDeleteShader(id);
         }
     }

     //Método que crea los shader
     void Shader::creaShader(int i, std::string codigoShader) {
         id = glCreateShader(i);
         if(i == GL_VERTEX_SHADER) {
             if(id == 0) {
                 std::cout << "Error creating vertex shader" << std::endl;
             } else {
                 compilarShader(codigoShader, id, "VertexShader"); //Función que compila el archivo que contiene el código fuente del shader y que lo une a un id
             }
         } else {
             if(i == GL_FRAGMENT_SHADER) {
                 if(id == 0) {
                     std::cout << "Error creating fragment shader" << std::endl;
                 } else {
                     compilarShader(codigoShader, id, "FragmentShader"); //Función que compila el archivo que contiene el código fuente del shader y que lo une a un id
                 }
             }
         }
     }

    //Método para obtener los archivos necesarios para formar los shaders
    std::string Shader::getArchivo(std::string archivo) {
         std::ifstream archivoShader;
         archivoShader.open(archivo);
         if (!archivoShader.is_open()) {
             std::cout << "Error al abrir el archivo" << std::endl;
         }
         std::stringstream streamShader;
         streamShader << archivoShader.rdbuf();
         std::string codigoFuenteShader = streamShader.str();
         archivoShader.close();
         return codigoFuenteShader;
     }

    //Método que compila los shaders y muestra si existe algún error en el shader elegido
    void Shader::compilarShader(std::string shader, GLuint id, std::string shaderType) {
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

    //Método para obtener el identificador del shader
    GLuint Shader::getId() {
         return id;
     }
} // PAG