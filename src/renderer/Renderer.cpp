#include "renderer/Renderer.hpp"

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {

        Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

        renderer->toggleFullscreen();
    }
}

Renderer::Renderer() : _window(nullptr), _title("Rubik"), _camera(*this) {

    _windowSize[WIDTH] = DEFAULT_WIDTH;
    _windowSize[HEIGHT] = DEFAULT_HEIGHT;
    _windowPos[X] = 0;
    _windowPos[Y] = 0;
    this->_fullscreen = false;
}

Renderer::~Renderer() {this->_cleanup();}

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

    this->toggleFullscreen();

    glfwMakeContextCurrent(this->_window);

    glfwSetWindowUserPointer(this->_window, this);
    glfwSetKeyCallback(this->_window, keyCallback);

    if (!gladLoaderLoadGL()) {

        std::cerr << "Failed to initialize GLAD\n";
        return (false);
    }

    glEnable(GL_DEPTH_TEST);
    this->_shader.init();
    this->_mesh.init();
    this->_camera.init();

    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    // (void)io;
    // ImGui::StyleColorsDark();

    // ImGui_ImplGlfw_InitForOpenGL(this->_window, true);
    // ImGui_ImplOpenGL3_Init("#version 460");

    return (true);
}

const int * Renderer::getWindowSize() const {return(this->_windowSize);};

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

    // temp
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // camera update
    this->_camera.updateProjection();
    this->_shader.setMat4(CAMERA, this->_camera.getMatrix());

    // temp rotate
    this->_mesh.rotate(0.005f, {0.0f, 1.0f, 0.0f});

    // cube update
    this->_shader.setMat4(MODEL, this->_mesh.getModel());
    this->_shader.setTexture();
    this->_mesh.draw();
}

void Renderer::renderLoop() {

    while (!glfwWindowShouldClose(this->_window)) {

        glfwGetFramebufferSize(this->_window, &this->_windowSize[WIDTH], &this->_windowSize[HEIGHT]);
        glfwPollEvents();

        _renderCube();
        // _renderGui();

        glfwSwapBuffers(this->_window);
    }
}

void Renderer::toggleFullscreen() {

    if (!this->_window)
        return ;
    this->_fullscreen = !this->_fullscreen;

    if (this->_fullscreen) {

        glfwGetWindowPos(this->_window, &this->_windowPos[X], &this->_windowPos[Y]);
        glfwGetWindowSize(this->_window, &this->_windowSize[WIDTH], &this->_windowSize[HEIGHT]);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(this->_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
        glfwSetWindowMonitor(_window, nullptr, this->_windowPos[X], this->_windowPos[Y], DEFAULT_WIDTH, DEFAULT_HEIGHT, 0);
    
    std::cout << this->_windowSize[WIDTH] << ", " << this->_windowSize[HEIGHT] << "\n";
}

void Renderer::_cleanup() {

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
