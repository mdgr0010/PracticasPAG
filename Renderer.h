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
            Renderer();
        public:
            virtual ~Renderer();
            static Renderer* getInstancia();
            void refrescar();
            void reedimensionar(int width, int height);
    };

} // PAG

#endif //RENDERER_H
