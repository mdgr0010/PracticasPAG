/**
 * @file Renderer.h
 * @author mdgr0010
 *
 * @date 20/09/2024
 *
 * @brief Declaración de la clase Renderer
 */

#ifndef RENDERER_H
#define RENDERER_H

//Espacio de nombres para las prácticas de Programación de Aplicaciones Gráficas
namespace PAG {
    /**
     * @brief Clase encargada de encapsular la gestión del área de dibujo
     *        OpenGL
     *
     * Esta clase coordina el reenderizado de las escenas OpenGL. Se implementa
     * aplicando el patrón de diseño Singleton. Está pensada para que las
     * funciones callback hagan llamadas a sus métodos
     */
    class Renderer {
        private:
            static Renderer* instancia; //Puntero al único objeto
            GLuint idVS = 0; //Identificador del vertex shader
            GLuint idFS = 0; //Identificador del fragment shader
            GLuint idSP = 0; //Identificador del shader program
            GLuint idVAO = 0; //Identificador del vertex array object
            GLuint idVBO = 0; //Identificador del vertex buffer object
            GLuint idIBO = 0; //Identificador del index buffer object
            Renderer();
        public:
            virtual ~Renderer();
            static Renderer* getInstancia();
            void refrescar();
            void reedimensionar(int width, int height);
            void cambioColor(double yoffset, float& red, float& green, float& blue, float incremento);
            void creaShaderProgram();
            void creaModelo();
            void inicializaOpenGL();
    };

} // PAG

#endif //RENDERER_H
