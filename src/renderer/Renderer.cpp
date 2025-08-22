#include "RubikController.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/Mesh.hpp"

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

Renderer::Renderer() : _window(nullptr), _title("Rubik"), _camera(*this, this->_shader), _rubiksCube(this->_shader) {

    this->_controller = 0;
    this->_windowSize[WIDTH] = DEFAULT_WIDTH;
    this->_windowSize[HEIGHT] = DEFAULT_HEIGHT;
    this->_windowPos[X] = 0;
    this->_windowPos[Y] = 0;
    this->_rotatingCam = false;
    this->_time = 0.0;
    this->_deltaTime = 0.0;
    this->_fps = 0.0;
    this->_currentStep = 0;
    this->_currentSpin = 0;
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

static void SetupImGuiStyle() {

	// Comfy style by Giuseppe from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.1000000014901161f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 10.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(30.0f, 30.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Right;
	style.ChildRounding = 5.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 10.0f;
	style.PopupBorderSize = 0.0f;
	style.FramePadding = ImVec2(5.0f, 3.5f);
	style.FrameRounding = 5.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(5.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(5.0f, 5.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 5.0f;
	style.ColumnsMinSpacing = 5.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 15.0f;
	style.GrabRounding = 5.0f;
	style.TabRounding = 5.0f;
	style.TabBorderSize = 0.0f;
	// style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(1.0f, 1.0f, 1.0f, 0.3605149984359741f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.4235294163227081f, 0.3803921639919281f, 0.572549045085907f, 0.54935622215271f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3803921639919281f, 0.4235294163227081f, 0.572549045085907f, 0.5490196347236633f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.6196078658103943f, 0.5764706134796143f, 0.7686274647712708f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2588235437870026f, 0.2588235437870026f, 0.2588235437870026f, 0.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 0.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.2352941185235977f, 0.2352941185235977f, 0.2352941185235977f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.6196078658103943f, 0.5764706134796143f, 0.7686274647712708f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8156862854957581f, 0.772549033164978f, 0.9647058844566345f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.6196078658103943f, 0.5764706134796143f, 0.7686274647712708f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.8156862854957581f, 0.772549033164978f, 0.9647058844566345f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.6196078658103943f, 0.5764706134796143f, 0.7686274647712708f, 0.5490196347236633f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.8156862854957581f, 0.772549033164978f, 0.9647058844566345f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.6196078658103943f, 0.5764706134796143f, 0.7686274647712708f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.8156862854957581f, 0.772549033164978f, 0.9647058844566345f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.6196078658103943f, 0.5764706134796143f, 0.7686274647712708f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.8156862854957581f, 0.772549033164978f, 0.9647058844566345f, 0.5490196347236633f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.6196078658103943f, 0.5764706134796143f, 0.7686274647712708f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.8156862854957581f, 0.772549033164978f, 0.9647058844566345f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.4509803950786591f, 1.0f, 0.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 0.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.6196078658103943f, 0.5764706134796143f, 0.7686274647712708f, 0.5490196347236633f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.4235294163227081f, 0.3803921639919281f, 0.572549045085907f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.4235294163227081f, 0.3803921639919281f, 0.572549045085907f, 0.2918455004692078f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.03433477878570557f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
}

bool Renderer::init(RubikController * controller) {

    this->_controller = controller;

    if (!glfwInit()) {

        std::cerr << "GLFW init failed\n";
        return (false);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    this->_shader.init();
    this->_camera.init();
    this->_rubiksCube.init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(this->_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    SetupImGuiStyle();

    return (true);
}

void Renderer::renderLoop() {

    int frameCount = 0;
    float sumDeltaTime = 0.0f;

    while (!glfwWindowShouldClose(this->_window)) {

        const float currentTime = glfwGetTime();

        this->_deltaTime = currentTime - this->_time;
        this->_time = currentTime;

        sumDeltaTime += this->_deltaTime;
        frameCount++;
        if(frameCount >= 30) {

            this->_fps = frameCount / sumDeltaTime;
            sumDeltaTime = 0.0f;
            frameCount = 0;
        }

        glfwGetFramebufferSize(this->_window, &this->_windowSize[WIDTH], &this->_windowSize[HEIGHT]);
        glViewport(0, 0, this->_windowSize[WIDTH], this->_windowSize[HEIGHT]);
        glfwPollEvents();

        _renderCube();
        _renderGui();

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

void Renderer::_renderGui() {

    ImVec2 windowSize = ImVec2( \
        static_cast<float>(this->_windowSize[WIDTH]), \
        static_cast<float>(this->_windowSize[HEIGHT]));
    ImVec2 buttonSize;
    static int shuffleValue = 20;
    static float guiZoom = GUI_SCALE_DEFAULT;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(windowSize);
    ImGui::Begin("HUD", nullptr, \
        ImGuiWindowFlags_NoDecoration \
        | ImGuiWindowFlags_NoBackground \
        | ImGuiWindowFlags_NoMove \
        | ImGuiWindowFlags_NoSavedSettings \
        | ImGuiWindowFlags_NoBringToFrontOnFocus);

    buttonSize = ImVec2(windowSize.x * 0.05f * guiZoom, windowSize.y * 0.05f * guiZoom);

    ImGui::SetCursorPos(ImVec2(windowSize.x - (buttonSize.x + GUI_BUTTON_OFFSET), GUI_BUTTON_OFFSET));
    if (ImGui::Button("X", buttonSize))
        glfwSetWindowShouldClose(this->_window, true);

    ImGui::SetCursorPos(ImVec2(windowSize.x - (buttonSize.x + GUI_BUTTON_OFFSET) * 2, GUI_BUTTON_OFFSET));
    if (ImGui::Button("[]", buttonSize))
        this->_toggleFullscreen();

    ImGui::SetCursorPos(ImVec2(windowSize.x - (buttonSize.x + GUI_BUTTON_OFFSET) * 3, GUI_BUTTON_OFFSET));
    if (ImGui::Button("_", buttonSize))
        glfwIconifyWindow(this->_window);

    ImGui::SetCursorPos(ImVec2(windowSize.x * 0.5f - buttonSize.x - 2, windowSize.y - buttonSize.y - GUI_BUTTON_OFFSET));
    if (ImGui::Button("Shuffle", buttonSize)) {

        this->_controller->generateRandomSpinLst(shuffleValue);
        this->_controller->applySuffle();
    }

    ImGui::SetCursorPos(ImVec2(windowSize.x * 0.5f + 2, windowSize.y - buttonSize.y - GUI_BUTTON_OFFSET));
    if (ImGui::Button("Solve", buttonSize))
        this->_controller->solve();

    if (!this->_solutionSteps.empty()) {

        const char * text = this->_solutionSteps[this->_currentStep].first.c_str();
        const ImVec2 textSize = ImGui::CalcTextSize(text);

        ImGui::SetCursorPos(ImVec2(windowSize.x * 0.5f - textSize.x * 0.5f, windowSize.y * 0.2f - textSize.y * 0.5f));
        ImGui::TextWrapped(text);

        ImGui::SetCursorPos(ImVec2(windowSize.x * 0.2f - buttonSize.x * 0.5f, windowSize.y * 0.5f - buttonSize.y * 0.5f));
        if (ImGui::Button("<-", buttonSize))
            this->_prevSpin();

        ImGui::SetCursorPos(ImVec2(windowSize.x * 0.8f - buttonSize.x * 0.5f, windowSize.y * 0.5f - buttonSize.y * 0.5f));
        if (ImGui::Button("->", buttonSize))
            this->_nextSpin();
    }

    ImGui::End();

    static bool collapsed = true;

    if (collapsed)
        ImGui::SetNextWindowPos(ImVec2(0, windowSize.y - ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f - 20));
    else
        ImGui::SetNextWindowPos(ImVec2(0, windowSize.y - (windowSize.y * 0.4f * guiZoom - 1.0f)));
    ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.3 * guiZoom, windowSize.y * 0.4f * guiZoom));
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings", nullptr, \
        ImGuiWindowFlags_NoMove \
        | ImGuiWindowFlags_NoSavedSettings \
        | ImGuiWindowFlags_NoResize);

    collapsed = ImGui::IsWindowCollapsed();

    if (ImGui::CollapsingHeader("Info", ImGuiTreeNodeFlags_DefaultOpen)) {

        ImGui::Text("FPS: %.1f", this->_fps);
    }

    if (ImGui::CollapsingHeader("Rubiks Cube", ImGuiTreeNodeFlags_DefaultOpen)) {

        static bool rotationAnimation = CUBE_ROTATION_ANIMATION_DEFAULT;
        static bool spinAnimation = CUBE_SPIN_ANIMATION_DEFAULT;
        static float rotationSpeed = CUBE_ROTATION_SPEED_DEFAULT;
        static float spinSpeed = CUBE_SPIN_SPEED_DEFAULT;

        ImGui::SetNextItemWidth(100 * guiZoom);
        if (ImGui::InputInt("Shuffle Depth", &shuffleValue, 1, 10) && shuffleValue < 0)
            shuffleValue *= -1;
        if (ImGui::Checkbox("Cube Rotation", &rotationAnimation))
            this->_rubiksCube.enableAnimation(CUBE_ROTATION_ANIMATION, rotationAnimation);
        if (rotationAnimation && ImGui::SliderFloat("Rotation Speed", &rotationSpeed, CUBE_ROTATION_SPEED_MIN, CUBE_ROTATION_SPEED_MAX))
            this->_rubiksCube.setAnimationSpeed(CUBE_ROTATION_ANIMATION, rotationSpeed);
        if (ImGui::Checkbox("Spin Animation", &spinAnimation))
            this->_rubiksCube.enableAnimation(CUBE_SPIN_ANIMATION, spinAnimation);
        if (spinAnimation && ImGui::SliderFloat("Spin Speed", &spinSpeed, CUBE_SPIN_SPEED_MIN, CUBE_SPIN_SPEED_MAX))
            this->_rubiksCube.setAnimationSpeed(CUBE_SPIN_ANIMATION, spinSpeed);
    }

    if (ImGui::CollapsingHeader("Graphiques", ImGuiTreeNodeFlags_DefaultOpen)) {

        static int fov = CAM_FOV_DEFAULT;
        static bool vsync = VSYNC_DEFAULT;
        static bool MSAA = MSAA_DEFAULT;

        if (ImGui::SliderFloat("GUI Scale", &guiZoom, GUI_SCALE_MIN, GUI_SCALE_MAX))
            ImGui::GetIO().FontGlobalScale = guiZoom;
        if (ImGui::SliderInt("Fov", &fov, CAM_FOV_MIN, CAM_FOV_MAX))
            this->_camera.setFov(fov);
        if (ImGui::Checkbox("V-Sync", &vsync))
            glfwSwapInterval(vsync);
        if (ImGui::Checkbox("MSAA x8", &MSAA)) {

            if (MSAA)
                glEnable(GL_MULTISAMPLE);
            else
                glDisable(GL_MULTISAMPLE);
        }
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::_renderCube() {

    glClearColor(0.3f, 0.4f, 0.55f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->_rubiksCube.animate(this->_deltaTime);
    this->_rubiksCube.draw();
}

void Renderer::_nextSpin() {

    if (this->_solutionSteps.empty())
        return;

    std::pair<std::string, std::pair<std::vector<SpinLst>, std::vector<SpinLst>>> & step \
        = this->_solutionSteps[this->_currentStep];

    if (this->_currentSpin < static_cast<int>(step.second.first.size())) {

        this->_rubiksCube.spin(step.second.first[this->_currentSpin], 0.2f);
        this->_currentSpin++;
    }
    else if (this->_currentStep + 1 < static_cast<int>(this->_solutionSteps.size())) {

        this->_currentStep++;
        this->_currentSpin = 0;
    }
}

void Renderer::_prevSpin() {

    if (this->_solutionSteps.empty())
        return;
        
    std::pair<std::string, std::pair<std::vector<SpinLst>, std::vector<SpinLst>>> & step \
        = this->_solutionSteps[this->_currentStep];

    if (this->_currentSpin > 0) {

        this->_currentSpin--;
        this->_rubiksCube.spin(step.second.second[this->_currentSpin], 0.2f);
    }
    else if (this->_currentStep > 0) {

        this->_currentStep--;
        this->_currentSpin = static_cast<int>(step.second.second.size()) - 1;
    }
}
