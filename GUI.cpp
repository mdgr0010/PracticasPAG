/**
* @file Renderer.cpp
 * @author mdgr0010
 *
 * @date 26/09/2024
 *
 * @brief Implementación de la clase GUI
 */

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "GUI.h"

#include <GLFW/glfw3.h>

namespace PAG {
    PAG::GUI*  PAG::GUI::instancia = nullptr;

    //Constructor por defecto
    GUI::GUI() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    }

    //Destructor
    GUI::~GUI() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    /**
     * Consulta del único objeto de la clase
     * @return La dirección de memoria del objeto
     */
    GUI *GUI::getInstancia() {
        if (!instancia) {
            instancia = new PAG::GUI();
        }
        return instancia;
    }

    void GUI::refrescar() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2 (10, 10), ImGuiCond_Once);

        if(ImGui::Begin("Mensajes")) {
            ImGui::SetWindowFontScale(1.0f);

            //Se dibujan los controles de Dear ImGui
            //Aquí va el dibujado de la escena con instrucciones OpenGL
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        ImGui::End();
    }

    void GUI::raton(int button, int pressed) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(button, pressed);
    }
} // PAG