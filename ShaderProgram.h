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
#include "Shader.h"

//Espacio de nombres para las prácticas de Programación de Aplicaciones Gráficas
namespace PAG {

    /**
     * @brief Clase encargada de encapsular la gestión de los Shader Program
     */
     class ShaderProgram {
         private:
            Shader vertexShader;
            Shader fragmentShader;
            std::string nombreShader = "pag03";
            GLuint idSP = 0; //Identificador del shader program
         public:
            ShaderProgram();
            ~ShaderProgram();
            void creaShaderProgram();
            void linkShaderProgram(GLuint id);
            void useProgram();
            //void setNombreShader(std::string nomShader);
     };
} // PAG

#endif //SHADERPROGRAM_H
