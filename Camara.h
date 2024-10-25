//
// Created by Lola on 25/10/2024.
//

#ifndef CAMARA_H
#define CAMARA_H

namespace PAG {


    class Camara {
        private:
            float pan;
            float tilt;
            float dolly;
            float orbit;
            float zoom;
        public:
            Camara();
            ~Camara();
            void init();
            void update();
            void render();
            GLfloat radianes(int anguloSexagesimal);
            glm::mat4 transVision(int pos, int lookAt, int up);
            glm::mat4 transProyeccion(int fovY, int aspecto, int zNear, int zFar);
            glm::mat4 translacion(int posicion, int otraPosicion);
            glm::mat4 rotacion(int angulo, glm::vec3 eje);
            glm::vec3 normaliza(glm::vec3 vector);
            glm::vec3 cruce(glm::vec3 vector1, glm::vec3 vector2);
            glm::bvec3 comparar(glm::vec3 vector1, glm::vec3 vector2);
    };

} // PAG

#endif //CAMARA_H
