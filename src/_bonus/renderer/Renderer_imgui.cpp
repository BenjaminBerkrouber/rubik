#include "renderer/Renderer.hpp"
#include "RubikController_bonus.hpp"

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

void Renderer::_renderGui() {

    ImVec2 windowSize = ImVec2( \
        static_cast<float>(this->_windowSize[WIDTH]), \
        static_cast<float>(this->_windowSize[HEIGHT]));
    ImVec2 buttonSize;
    static int shuffleValue = 20;
    static float guiZoom = GUI_SCALE_DEFAULT;
    static int solveAlgo = SOLVER_KOCIEMBA;
    static bool randomShuffle = true;
    static char spinBuffer[1024] = "R F2 U' R ...";
    static bool solved = false;
    static bool shuffled = false;

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

        this->_controller->reset();
        this->_rubiksCube.resetPos();
        if (randomShuffle)
            this->_controller->generateRandomSpinLst(shuffleValue);
        else {

            this->_controller->parse(spinBuffer);
            this->_controller->applySuffle();
            this->setShuffleSpins(this->_controller->getShuffle());
        }
        shuffled = true;
        solved = false;
    }

    ImGui::SetCursorPos(ImVec2(windowSize.x * 0.5f + 2, windowSize.y - buttonSize.y - GUI_BUTTON_OFFSET));
    if (!shuffled || solved) {

        ImGui::BeginDisabled();
        ImGui::Button("Solve", buttonSize);
        ImGui::EndDisabled();
    }
    else if (ImGui::Button("Solve", buttonSize)) {

        this->_controller->solve(solveAlgo);
        solved = true;
    }

    if (solved) {

        const char * text = this->_solutionSteps[this->_currentStep].first.c_str();
        const ImVec2 textSize = ImGui::CalcTextSize(text);

        ImGui::SetCursorPos(ImVec2(windowSize.x * 0.5f - textSize.x * 0.5f, windowSize.y * 0.2f - textSize.y * 0.5f));
        ImGui::TextWrapped("%s", text);

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
        ImGui::SetNextWindowPos(ImVec2(0, windowSize.y - ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f - 12));
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

        ImGui::TextWrapped("FPS: %.1f", this->_fps);
        if (!this->_shuffleSpins.empty() && ImGui::TreeNode("Last Shuffle:")) {

            ImGui::TextWrapped("Spins: %ld", this->_shuffleSpinsStr.size());
            ImGui::TextWrapped("Spins List: %s", this->_shuffleSpinsStr.c_str());
            ImGui::SameLine();
            if (ImGui::Button("Copy"))
                ImGui::SetClipboardText(this->_shuffleSpinsStr.c_str());
            ImGui::TreePop();
        }
        if (!this->_solutionSteps.empty() && ImGui::TreeNode("Last Solve:")) {

            ImGui::TextWrapped("Solve Time: %f", this->_solveTime);
            ImGui::TextWrapped("Spins: %ld", this->_solutionSpins.size());
            ImGui::TextWrapped("Spins List: %s", this->_solutionSpinsStr.c_str());
            ImGui::SameLine();
            if (ImGui::Button("Copy"))
                ImGui::SetClipboardText(this->_solutionSpinsStr.c_str());
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Rubiks Cube", ImGuiTreeNodeFlags_DefaultOpen)) {

        static bool rotationAnimation = CUBE_ROTATION_ANIMATION_DEFAULT;
        static bool spinAnimation = CUBE_SPIN_ANIMATION_DEFAULT;
        static float rotationSpeed = CUBE_ROTATION_SPEED_DEFAULT;
        static float spinSpeed = CUBE_SPIN_SPEED_DEFAULT;

        if (ImGui::TreeNode("Algo:")) {

            ImGui::TextWrapped("Solver Method:");
            ImGui::SameLine();
            ImGui::RadioButton("Minimal Spins", &solveAlgo, 0);
            ImGui::SameLine();
            ImGui::RadioButton("Fastest", &solveAlgo, 1);
            ImGui::Checkbox("Random Shuffle", &randomShuffle);
            if (randomShuffle && ImGui::InputInt("Shuffle Depth", &shuffleValue, 1, 10) && shuffleValue < 0)
                shuffleValue *= -1;
            else if (!randomShuffle) {

                if (ImGui::Button("Copy"))
                    ImGui::SetClipboardText(spinBuffer);
                ImGui::SameLine();
                if (ImGui::Button("Paste")) {

                    strncpy(spinBuffer, ImGui::GetClipboardText(), IM_ARRAYSIZE(spinBuffer));
                    spinBuffer[IM_ARRAYSIZE(spinBuffer) - 1] = '\0';
                }
                ImGui::InputText("Spin List", spinBuffer, IM_ARRAYSIZE(spinBuffer));
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Animations:")) {

            if (ImGui::Checkbox("Cube Rotation", &rotationAnimation))
                this->_rubiksCube.setAnimationState(CUBE_ROTATION_ANIMATION, rotationAnimation);
            if (rotationAnimation && ImGui::SliderFloat("Rotation Speed", &rotationSpeed, CUBE_ROTATION_SPEED_MIN, CUBE_ROTATION_SPEED_MAX))
                this->_rubiksCube.setAnimationSpeed(CUBE_ROTATION_ANIMATION, rotationSpeed);
            if (ImGui::Checkbox("Spin Animation", &spinAnimation))
                this->_rubiksCube.setAnimationState(CUBE_SPIN_ANIMATION, spinAnimation);
            if (spinAnimation && ImGui::SliderFloat("Spin Speed", &spinSpeed, CUBE_SPIN_SPEED_MIN, CUBE_SPIN_SPEED_MAX))
                this->_rubiksCube.setAnimationSpeed(CUBE_SPIN_ANIMATION, spinSpeed);
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Graphics", ImGuiTreeNodeFlags_DefaultOpen)) {

        static int fov = CAM_FOV_DEFAULT;
        static bool vsync = VSYNC_DEFAULT;
        static bool MSAA = MSAA_DEFAULT;

        if (ImGui::TreeNode("Interface:")) {

            static int stylePreset = 2;
            static int rounding = 1;

            if (ImGui::SliderFloat("Scale", &guiZoom, GUI_SCALE_MIN, GUI_SCALE_MAX))
                ImGui::GetIO().FontGlobalScale = guiZoom;
            ImGui::TextWrapped("Style:");
            ImGui::SameLine();
            if (ImGui::RadioButton("Default Light", &stylePreset, 0))
                this->_setupImGuiStyle(stylePreset, rounding);
            ImGui::SameLine();
            if (ImGui::RadioButton("Default Dark", &stylePreset, 1))
                this->_setupImGuiStyle(stylePreset, rounding);
            ImGui::SameLine();
            if (ImGui::RadioButton("Comfy Cherry", &stylePreset, 2))
                this->_setupImGuiStyle(stylePreset, rounding);
            ImGui::SameLine();
            if (ImGui::RadioButton("Comfy Cyan", &stylePreset, 3))
                this->_setupImGuiStyle(stylePreset, rounding);

            ImGui::TextWrapped("Rounding:");
            ImGui::SameLine();
            if (ImGui::RadioButton("True", &rounding, 1))
                this->_setupImGuiStyle(stylePreset, rounding);
            ImGui::SameLine();
            if (ImGui::RadioButton("False", &rounding, 0))
                this->_setupImGuiStyle(stylePreset, rounding);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Camera:")) {

            if (ImGui::SliderInt("FOV", &fov, CAM_FOV_MIN, CAM_FOV_MAX))
                this->_camera.setFov(fov);
            if (ImGui::Checkbox("V-Sync", &vsync))
                glfwSwapInterval(vsync);
            ImGui::SameLine();
            if (ImGui::Checkbox("MSAA x8", &MSAA)) {

                if (MSAA)
                    glEnable(GL_MULTISAMPLE);
                else
                    glDisable(GL_MULTISAMPLE);
            }

            ImGui::TreePop();
        }
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

static void SetDefaultLight(ImGuiStyle & style)
{
	// Light style by dougbinks from ImThemes

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.6000000238418579f, 0.6000000238418579f, 0.6000000238418579f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.9372549057006836f, 0.9372549057006836f, 0.9372549057006836f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.9800000190734863f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.300000011920929f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.4000000059604645f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.6700000166893005f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.95686274766922f, 0.95686274766922f, 0.95686274766922f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.8196078538894653f, 0.8196078538894653f, 0.8196078538894653f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.0f, 1.0f, 1.0f, 0.5099999904632568f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.8588235378265381f, 0.8588235378265381f, 0.8588235378265381f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.9764705896377563f, 0.9764705896377563f, 0.9764705896377563f, 0.5299999713897705f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.686274528503418f, 0.686274528503418f, 0.686274528503418f, 0.800000011920929f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4862745106220245f, 0.4862745106220245f, 0.4862745106220245f, 0.800000011920929f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.4862745106220245f, 0.4862745106220245f, 0.4862745106220245f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.7799999713897705f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.4588235318660736f, 0.5372549295425415f, 0.800000011920929f, 0.6000000238418579f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.4000000059604645f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.05882352963089943f, 0.529411792755127f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3100000023841858f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.800000011920929f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.3882353007793427f, 0.3882353007793427f, 0.3882353007793427f, 0.6200000047683716f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1372549086809158f, 0.4392156898975372f, 0.800000011920929f, 0.7799999713897705f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1372549086809158f, 0.4392156898975372f, 0.800000011920929f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.3490196168422699f, 0.3490196168422699f, 0.3490196168422699f, 0.1700000017881393f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.6700000166893005f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.949999988079071f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.7607843279838562f, 0.7960784435272217f, 0.8352941274642944f, 0.9309999942779541f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.800000011920929f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.5921568870544434f, 0.7254902124404907f, 0.8823529481887817f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.9176470637321472f, 0.9254902005195618f, 0.9333333373069763f, 0.9861999750137329f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.7411764860153198f, 0.8196078538894653f, 0.9137254953384399f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.3882353007793427f, 0.3882353007793427f, 0.3882353007793427f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.4470588266849518f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.7764706015586853f, 0.8666666746139526f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.5686274766921997f, 0.5686274766921997f, 0.6392157077789307f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.6784313917160034f, 0.6784313917160034f, 0.7372549176216125f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.2980392277240753f, 0.2980392277240753f, 0.2980392277240753f, 0.09000000357627869f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.949999988079071f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.800000011920929f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.6980392336845398f, 0.6980392336845398f, 0.6980392336845398f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.3499999940395355f);
}

static void SetDefaultDark(ImGuiStyle & style)
{
	// Default Dark style by Parinder

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.6f;
    style.WindowPadding = ImVec2(8.0f, 8.0f);
    style.WindowRounding = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.FrameRounding = 0.0f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.CellPadding = ImVec2(4.0f, 2.0f);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 14.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 12.0f;
    style.GrabRounding = 0.0f;
    style.TabRounding = 5.0f;
    style.TabBorderSize = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[0] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[1] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    style.Colors[2] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    style.Colors[3] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[4] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    style.Colors[5] = ImVec4(0.43f, 0.43f, 0.5f, 0.5f);
    style.Colors[6] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[7] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
    style.Colors[8] = ImVec4(0.26f, 0.59f, 0.98f, 0.4f);
    style.Colors[9] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[10] = ImVec4(0.04f, 0.04f, 0.04f, 1.0f);
    style.Colors[11] = ImVec4(0.16f, 0.29f, 0.48f, 1.0f);
    style.Colors[12] = ImVec4(0.0f, 0.0f, 0.0f, 0.51f);
    style.Colors[13] = ImVec4(0.14f, 0.14f, 0.14f, 1.0f);
    style.Colors[14] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    style.Colors[15] = ImVec4(0.31f, 0.31f, 0.31f, 1.0f);
    style.Colors[16] = ImVec4(0.41f, 0.41f, 0.41f, 1.0f);
    style.Colors[17] = ImVec4(0.51f, 0.51f, 0.51f, 1.0f);
    style.Colors[18] = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
    style.Colors[19] = ImVec4(0.24f, 0.52f, 0.88f, 1.0f);
    style.Colors[20] = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
    style.Colors[21] = ImVec4(0.26f, 0.59f, 0.98f, 0.4f);
    style.Colors[22] = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
    style.Colors[23] = ImVec4(0.06f, 0.53f, 0.98f, 1.0f);
    style.Colors[24] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    style.Colors[25] = ImVec4(0.26f, 0.59f, 0.98f, 0.8f);
    style.Colors[26] = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
    style.Colors[27] = ImVec4(0.43f, 0.43f, 0.5f, 0.5f);
    style.Colors[28] = ImVec4(0.1f, 0.4f, 0.75f, 0.78f);
    style.Colors[29] = ImVec4(0.1f, 0.4f, 0.75f, 1.0f);
    style.Colors[30] = ImVec4(0.26f, 0.59f, 0.98f, 0.2f);
    style.Colors[31] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[32] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[33] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[34] = ImVec4(0.26f, 0.59f, 0.98f, 0.8f);
    style.Colors[35] = ImVec4(0.18f, 0.35f, 0.58f, 0.862f);
    style.Colors[36] = ImVec4(0.2f, 0.41f, 0.68f, 1.0f);
    style.Colors[37] = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
    style.Colors[38] = ImVec4(0.068f, 0.102f, 0.148f, 0.9724f);
    style.Colors[39] = ImVec4(0.136f, 0.262f, 0.424f, 1.0f);
    style.Colors[40] = ImVec4(0.5f, 0.5f, 0.5f, 0.0f);
    style.Colors[41] = ImVec4(0.26f, 0.59f, 0.98f, 0.7f);
    style.Colors[42] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    style.Colors[43] = ImVec4(0.61f, 0.61f, 0.61f, 1.0f);
    style.Colors[44] = ImVec4(1.0f, 0.43f, 0.35f, 1.0f);
    style.Colors[45] = ImVec4(0.9f, 0.7f, 0.0f, 1.0f);
    style.Colors[46] = ImVec4(1.0f, 0.6f, 0.0f, 1.0f);
    style.Colors[47] = ImVec4(0.19f, 0.19f, 0.2f, 1.0f);
    style.Colors[48] = ImVec4(0.31f, 0.31f, 0.35f, 1.0f);
    style.Colors[49] = ImVec4(0.23f, 0.23f, 0.25f, 1.0f);
    style.Colors[50] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[51] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
    style.Colors[52] = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
    style.Colors[53] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style.Colors[54] = ImVec4(0.43f, 0.43f, 0.5f, 0.5f);
    style.Colors[55] = ImVec4(1.0f, 1.0f, 0.0f, 0.9f);
    style.Colors[56] = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
    style.Colors[57] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
    style.Colors[58] = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
    style.Colors[59] = ImVec4(0.8f, 0.8f, 0.8f, 0.35f);
}

static void SetComfy(ImGuiStyle & style) {

	// Comfy style by Giuseppe from ImThemes

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

static void SetComfyCyan(ImGuiStyle & style) {

	// Comfortable Dark Cyan style by SouthCraftX from ImThemes

	style.Alpha = 1.0f;
	style.DisabledAlpha = 1.0f;
	style.WindowPadding = ImVec2(20.0f, 20.0f);
	style.WindowRounding = 11.5f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(20.0f, 20.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_None;
	style.ChildRounding = 20.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 17.39999961853027f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(20.0f, 3.400000095367432f);
	style.FrameRounding = 11.89999961853027f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.899999618530273f, 13.39999961853027f);
	style.ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
	style.CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
	style.IndentSpacing = 0.0f;
	style.ColumnsMinSpacing = 8.699999809265137f;
	style.ScrollbarSize = 11.60000038146973f;
	style.ScrollbarRounding = 15.89999961853027f;
	style.GrabMinSize = 3.700000047683716f;
	style.GrabRounding = 20.0f;
	style.TabRounding = 9.800000190734863f;
	style.TabBorderSize = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.09411764889955521f, 0.1019607856869698f, 0.1176470592617989f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1137254908680916f, 0.125490203499794f, 0.1529411822557449f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0313725508749485f, 0.9490196108818054f, 0.843137264251709f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.0313725508749485f, 0.9490196108818054f, 0.843137264251709f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.6000000238418579f, 0.9647058844566345f, 0.0313725508749485f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1803921610116959f, 0.1882352977991104f, 0.196078434586525f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1529411822557449f, 0.1529411822557449f, 0.1529411822557449f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.1411764770746231f, 0.1647058874368668f, 0.2078431397676468f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.105882354080677f, 0.105882354080677f, 0.105882354080677f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.1294117718935013f, 0.1490196138620377f, 0.1921568661928177f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1450980454683304f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0313725508749485f, 0.9490196108818054f, 0.843137264251709f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.125490203499794f, 0.2745098173618317f, 0.572549045085907f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0313725508749485f, 0.9490196108818054f, 0.843137264251709f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9372549057006836f, 0.9372549057006836f, 0.9372549057006836f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2666666805744171f, 0.2901960909366608f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
}

void Renderer::_setupImGuiStyle(const int stylePreset, const bool rounded) {

    static ImGuiStyle & style = ImGui::GetStyle();
    static void (* setStyle[])(ImGuiStyle & style) = {SetDefaultLight, SetDefaultDark, SetComfy, SetComfyCyan};

    setStyle[stylePreset](style);
    if (rounded) {

        style.WindowRounding = 11.5f;
        style.ChildRounding = 20.0f;
        style.PopupRounding = 17.4f;
        style.FrameRounding = 11.9f;
        style.ScrollbarRounding = 15.9f;
        style.GrabRounding = 20.0f;
        style.TabRounding = 9.8f;
    }
    else {

        style.WindowRounding = 0.0f;
        style.ChildRounding = 0.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupRounding = 0.0f;
        style.FrameRounding = 0.0f;
        style.ScrollbarRounding = 9.0f;
        style.GrabRounding = 0.0f;
        style.TabRounding = 4.0f;
    }
    return ;
}
