/**
* @file ShaderProgram.h
 * @author mdgr0010
 *
 * @date 04/10/2024
 *
 * @brief Declaración de la clase ShaderProgram
 */
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

//Espacio de nombres para las prácticas de Programación de Aplicaciones Gráficas
namespace PAG {
    /**
     * @brief Clase encargada de encapsular la gestión de los Shader Program
     */
     class ShaderProgram {
         private:
            GLuint idVS = 0; //Identificador del vertex shader
            GLuint idFS = 0; //Identificador del fragment shader
            GLuint idSP = 0; //Identificador del shader program

         public:
            ShaderProgram();
            ~ShaderProgram();
            void creaShaderProgram();
            std::string getArchivo(std::string archivo);
            void compilarShader(std::string shader, GLuint id, std::string shaderType);
            void linkShaderProgram(GLuint id);
            void useProgram();
     };
} // PAG

#endif //SHADERPROGRAM_H
