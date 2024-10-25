#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Camara.h"

namespace PAG {
    Camara::Camara() {

    }

    Camara::~Camara() {

    }

    void Camara::init() {}

    void Camara::update() {}

    void Camara::render() {}

    GLfloat Camara::radianes(int anguloSexagesimal) {
        GLfloat anguloRadianes = glm::radians(anguloSexagesimal);
        return anguloRadianes;
    }

    glm::mat4 Camara::transVision(int pos, int lookAt, int up) {
        glm::mat4 matriz = glm::lookAt(pos, lookAt, up);
        return matriz;
    }

    glm::mat4 Camara::transProyeccion(int fovY, int aspecto, int zNear, int zFar) {
        glm::mat4 matriz = glm::perspective(fovY, aspecto, zNear, zFar);
        return matriz;
    }

    glm::mat4 Camara::translacion(int posicion, int otraPosicion) {
        glm::mat4 m1 = glm::translate(posicion); //Devuelve una matriz con solo la traslacion

        glm::mat4 m2 = glm::translate(m1, otraPosicion); //Calcula la traslacion, multiplica m1*traslacion y devuelve el resultado

        return m2;
    }

    glm::mat4 Camara::rotacion(int angulo, glm::vec3 eje) {
        glm::mat4 m1 = glm::rotate(angulo, eje); //Devuelve una matriz con solo la rotacion

        glm::mat4 m2 = glm::rotate(m1, angulo, eje); // Calcula la rotación, multiplica m1*rotacion y devuelve el resultado. m1 no cambia

        return m2;
    }

    glm::vec3 Camara::normaliza(glm::vec3 vector) {
        glm::vec3 normalizado = glm::normalize(vector);
        return normalizado;
    }

    glm::vec3 Camara::cruce(glm::vec3 vector1, glm::vec3 vector2) {
        glm::vec3 v3 = glm::cross(vector1, vector2);
        return normalize(v3);
    }

    glm::bvec3 Camara::comparar(glm::vec3 vector1, glm::vec3 vector2) {
        glm::bvec3 v3 = equal(vector1, vector2, glm::epsilon<float>());
        return v3;
    }


} // PAG