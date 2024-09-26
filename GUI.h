/**
* @file GUI.h
 * @author mdgr0010
 *
 * @date 26/09/2024
 *
 * @brief Declaración de la clase GUI
 */

#ifndef GUI_H
#define GUI_H
#include <GLFW/glfw3.h>

//Espacio de nombres para las prácticas de Programación de Aplicaciones Gráficas
namespace PAG {

 /**
     * @brief Clase encargada de encapsular la gestión de Dear ImGui
     */
    class GUI {
        private:
            static GUI* instancia;
            GUI();
        public:
            virtual ~GUI();
            static GUI* getInstancia();
            void refrescar();
            void raton(int button, int pressed);
    };

} // PAG

#endif //GUI_H
