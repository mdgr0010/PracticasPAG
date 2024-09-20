/**
 * @file Renderer.cpp
 * @author mdgr0010
 *
 * @date 20/09/2024
 *
 * @brief Implementación de la clase Renderer
 */

#include <glad//glad.h>

#include "Renderer.h"

namespace PAG {
    PAG::Renderer* PAG::Renderer::instancia = nullptr;

    //Constructor por defecto
    Renderer::Renderer() {

    }

    //Destructor
    Renderer::~Renderer() {

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


} // PAG