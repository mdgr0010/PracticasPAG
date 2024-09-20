/**
 * @file Renderer.cpp
 * @author mdgr0010
 *
 * @date 20/09/2024
 *
 * @brief Implementación de la clase Renderer
 */

#include <GL/glew.h>

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

} // PAG