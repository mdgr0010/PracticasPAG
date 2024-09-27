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

//Espacio de nombres para las prácticas de Programación de Aplicaciones Gráficas
namespace PAG {

/**
 * @brief Clase encargada de encapsular la gestión de Dear ImGui
 */
    class GUI {
        private:
            static GUI* instancia;
            std::vector<std::string> logs;//Vector para almacenar los mensajes del log
            GUI();
        public:
            virtual ~GUI();
            static GUI* getInstancia();
            void init(GLFWwindow* window);
            void newFrame();
            void render();
            void cleanup();
            void showColorPicker(float backgroundColor[]);
            void showConsoleWindow();
            void AddLog(const char* fmt, ...);
    };

} // PAG

#endif //GUI_H
