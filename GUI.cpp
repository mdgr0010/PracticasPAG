/**
/**
* @file Renderer.cpp
 * @author mdgr0010
 *
 * @date 26/09/2024
 *
 * @brief Implementación de la clase GUI
*/

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "GUI.h"



namespace PAG {
    PAG::GUI*  PAG::GUI::instancia = nullptr;

    //Constructor por defecto
    GUI::GUI() {
    }

    //Destructor
    GUI::~GUI() {
    }

    /**
     *Consulta del único objeto de la clase
     * @return La dirección de memoria del objeto
     */
    GUI *GUI::getInstancia() {
        if (!instancia) {
            instancia = new PAG::GUI();
        }
        return instancia;
    }

    //Función de inicialización
    void GUI::init(GLFWwindow* window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //Enable keyboard navigation

        ImGui_ImplGlfw_InitForOpenGL(window, true); //Set up platform/renderer bindings
        ImGui_ImplOpenGL3_Init();
    }

    //Función para empezar un nuevo frame
    void GUI::newFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    //Función render de ImGui
    void GUI::render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    //Función de limpieza
    void GUI::cleanup() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    //Función color picker
    void GUI::showColorPicker(float backgroundColor[]) {
        if (ImGui::Begin("Color Picker")) {
            //La ventana está desplegada
            //Pintamos los controles
            ImGui::ColorEdit3("Background Color", (float*) backgroundColor,
                              ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview |
                              ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
            glClearColor(backgroundColor[0],backgroundColor[1],backgroundColor[2], 1.0f);
        }
        //Si la ventana no está desplegada, Begin devuelve false
        ImGui::End();
    }

    //Función para mostrar los mensajes de consola en la ventana
    void GUI::showConsoleWindow() {
        if(ImGui::Begin("Mensajes")) {
            for (auto& log : logs) {
                ImGui::TextUnformatted(log.c_str());
            }

            if(ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                 ImGui::SetScrollHereY(1.0f);
            }
        }
        ImGui::End();
    }

    //Función para agregar los logs
    void GUI::AddLog(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        char buffer[1024];
        vsnprintf(buffer, IM_ARRAYSIZE(buffer), fmt, args);
        va_end(args);
        logs.push_back(std::string(buffer));
    }
} // PAG