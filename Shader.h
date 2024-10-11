/**
* @file Shader.h
 * @author mdgr0010
 *
 * @date 04/10/2024
 *
 * @brief Declaración de la clase Shader
 */
#ifndef SHADER_H
#define SHADER_H

//Espacio de nombres para las prácticas de Programación de Aplicaciones Gráficas
namespace PAG {

    /**
     * @brief Clase encargada de encapsular la gestión de los Shader
     */
     class Shader {
         private:
            GLuint id; //Identificador del shader
         public:
            Shader();
            ~Shader();
            void creaShader(int i, std::string codigoShader);
            std::string getArchivo(std::string archivo);
            void compilarShader(std::string shader, GLuint id, std::string shaderType);
            GLuint getId();
     };
} // PAG

#endif //SHADER_H
