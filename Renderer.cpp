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
    GLfloat PAG::Renderer::vertices[] = { -.5, -.5, 0,
                                           .5, -.5, 0,
                                           .0, .5, 0,};
    GLuint PAG::Renderer::indices[] = { 0, 1, 2,};

    //Constructor por defecto
    Renderer::Renderer() {
        shaderProgram.creaShaderProgram();
        creaModelo();
    }

    //Destructor
    Renderer::~Renderer() {
        if(idVBO != 0) {
            glDeleteBuffers(1, &idVBO);
        }

        if(idIBO != 0) {
            glDeleteBuffers(1, &idIBO);
        }

        if(idVAO != 0) {
            glDeleteVertexArrays(1, &idVAO);
        }
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
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        shaderProgram.useProgram();
        glBindVertexArray(idVAO); //Función para activar el VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO); //Función para indicarle al programa cual es la geometria a utilizar
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr); //Función que permite el proceso de rendering
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

    /**
     * Método para crear el VAO para el modelo a renderizar
     */
    void Renderer::creaModelo() {
        glGenVertexArrays(1, &idVAO); //Función para la creación del VAO, en este caso se crea en el idVAO que hemos creado previamente
        glBindVertexArray(idVAO); //Función que activa el VAO creado en la línea anterior
        glGenBuffers(1, &idVBO); //Función para la creación del VBO, en este caso, se crea en el idVBO que hemos creado previamente
        glBindBuffer(GL_ARRAY_BUFFER, idVBO); //Función que activa el VBO creado en la línea anterior, GL_ARRAY_BUFFER indica que se van a guardar atributos de vértices
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); //Función que le muestra al VBO la información que necesita para completarse
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL); //Función para indicar como están organizados los datos de un atributo del vértice en el VBO activo
        glEnableVertexAttribArray(0); //Función que activa un atributo de vértice almacenado en el VAO activo
        glGenBuffers(1, &idIBO); //Función para la creación del IBO, en este caso se crea uno en el idIBO que hemos creado previamente
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO); //Función que activa el  IBO creado en la línea anterior, GL_ELEMENT_ARRAY_BUFFER indica que los datos aportados anteriormente son los que hay que utilizar
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW); //Función que le muestra al IBO la información que necesita para completarse
    }

    /**
     * Método para inicializar los parámetros globales de OpenGL
     */
    void Renderer::inicializaOpenGL() {
        glEnable(GL_DEPTH_TEST); //Función que activa el algoritmo del Z-Buffer
        glEnable(GL_MULTISAMPLE); //Función para activar el antialiasing
    }
} // PAG