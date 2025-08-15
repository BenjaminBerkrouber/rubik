#include "renderer/Renderer.hpp"
#include "renderer/Mesh.hpp"

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

Renderer::Renderer() : _window(nullptr), _title("Rubik"), _camera(*this, this->_shader), _rubiksCube(this->_shader) {

    this->_windowSize[WIDTH] = DEFAULT_WIDTH;
    this->_windowSize[HEIGHT] = DEFAULT_HEIGHT;
    this->_windowPos[X] = 0;
    this->_windowPos[Y] = 0;
    this->_rotatingCam = false;
}

Renderer::~Renderer() {

    if (ImGui::GetCurrentContext()) {

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    if (this->_window) {

        glfwDestroyWindow(this->_window);
        this->_window = nullptr;
    }
    glfwTerminate();
}

const int * Renderer::getWindowSize() const {return(this->_windowSize);};

bool Renderer::init() {

    if (!glfwInit()) {

        std::cerr << "GLFW init failed\n";
        return (false);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->_window = glfwCreateWindow(this->_windowSize[WIDTH], this->_windowSize[HEIGHT], this->_title.c_str(), nullptr, nullptr);
    if (!this->_window) {

        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return (false);
    }

    this->_toggleFullscreen();

    glfwMakeContextCurrent(this->_window);

    glfwSetWindowUserPointer(this->_window, this);
    glfwSetKeyCallback(this->_window, staticKeyCallback);
    glfwSetMouseButtonCallback(this->_window, staticMouseButtonCallback);
    glfwSetCursorPosCallback(this->_window, staticCursorPosCallback);
    glfwSetScrollCallback(this->_window, staticScrollCallback);

    if (!gladLoaderLoadGL()) {

        std::cerr << "Failed to initialize GLAD\n";
        return (false);
    }

    glEnable(GL_DEPTH_TEST);
    this->_shader.init();
    this->_camera.init();
    this->_rubiksCube.init();

    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    // (void)io;
    // ImGui::StyleColorsDark();

    // ImGui_ImplGlfw_InitForOpenGL(this->_window, true);
    // ImGui_ImplOpenGL3_Init("#version 460");

    return (true);
}

void Renderer::renderLoop() {

    while (!glfwWindowShouldClose(this->_window)) {

        glfwGetFramebufferSize(this->_window, &this->_windowSize[WIDTH], &this->_windowSize[HEIGHT]);
        glViewport(0, 0, this->_windowSize[WIDTH], this->_windowSize[HEIGHT]);
        glfwPollEvents();

        _renderCube();
        // _renderGui();

        glfwSwapBuffers(this->_window);
    }
}

void Renderer::_toggleFullscreen() {

    static bool fullscreen = false;

    if (!this->_window)
        return ;
    fullscreen = !fullscreen;

    if (fullscreen) {

        static GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        static const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwGetWindowPos(this->_window, &this->_windowPos[X], &this->_windowPos[Y]);
        glfwGetWindowSize(this->_window, &this->_windowSize[WIDTH], &this->_windowSize[HEIGHT]);
        glfwSetWindowMonitor(this->_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
        glfwSetWindowMonitor(this->_window, nullptr, this->_windowPos[X], this->_windowPos[Y], DEFAULT_WIDTH, DEFAULT_HEIGHT, 0);
}

// void Renderer::_renderGui() {

//     // temp imgui ui
//     ImGui_ImplOpenGL3_NewFrame();
//     ImGui_ImplGlfw_NewFrame();
//     ImGui::NewFrame();

//     ImGui::Begin("Rubik Menu");

//     if (ImGui::Button("Mélanger le cube")) {
//         // Appelle ta logique de mélange ici
//     }

//     if (ImGui::Button("Résoudre le cube")) {
//         // Logique pour résoudre
//     }

//     if (ImGui::Button("Quitter")) {

//         glfwSetWindowShouldClose(this->_window, true);
//     }

//     if (ImGui::CollapsingHeader("Aide")) {

//         ImGui::Text("F11: Plein écran");
//         ImGui::Text("ESC: Quitter");
//         // Ajoute d'autres raccourcis
//     }

//     ImGui::Text("Instructions de mélange:");
//     ImGui::TextWrapped("U R U' L' F2 B ..."); // Remplace dynamiquement

//     ImGui::End();

//     // === Fin de UI ===
//     ImGui::Render();

//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
// }

void Renderer::_renderCube() {

    glClearColor(0.5f, 0.6f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // // temp rotate
    // this->_rubiksCube.spin(U);

    // cube update
    this->_rubiksCube.draw();
}
