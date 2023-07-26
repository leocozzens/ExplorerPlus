// C++ standard libs
#include <iostream>
#include <cstdlib>
// External libs
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// Local headers
#include <interface.hpp>

#define UTIL_CHECK(_Util, _Failure, _Err) if(!(_Util)) { std::cerr << "ERROR: Failed " << (_Failure) << '\n'; std::exit(_Err); }
#define UTIL_CHECK_TERM(_Util, _Failure, _Termination, _Err) if((_Util) == nullptr) { std::cerr << "ERROR: Failed " << (_Failure) << '\n'; _Termination; std::exit(_Err); }

#define WINDOW_NAME "ExplorerPlus"
#define WIDTH_ASPECT 0.55
#define HEIGHT_ASPECT 0.45

//Constructor/Destructor
Interface::Interface(void) {
    UTIL_CHECK(glfwInit(), "GLFW init", EXIT_FAILURE);

    int winWidth, winHeight;
    establish_window_height(winWidth, winHeight);
    this->mainWin = glfwCreateWindow(winWidth, winHeight, WINDOW_NAME, nullptr, nullptr);
    UTIL_CHECK_TERM(this->mainWin, "GLFW window", glfwTerminate(), EXIT_FAILURE);
    glfwMakeContextCurrent(this->mainWin);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    this->io = &(ImGui::GetIO()); 
    (void)(*io);
    this->io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    this->io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    this->io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    this->io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (this->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->mainWin, true);
    ImGui_ImplOpenGL3_Init();
}

// Static methods
void Interface::establish_window_height(int &winWidth, int &winHeight) {
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    UTIL_CHECK_TERM(primaryMonitor, "GLFW monitor", glfwTerminate(), EXIT_FAILURE);
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
    UTIL_CHECK_TERM(mode, "GLFW mode", glfwTerminate(), EXIT_FAILURE);
    winWidth = mode->width * WIDTH_ASPECT;
    winHeight = mode->height * HEIGHT_ASPECT;
}

// Instance methods
void Interface::event_loop(void) {
    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while(!glfwWindowShouldClose(this->mainWin)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(this->mainWin, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (this->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(this->mainWin);
    }
}

void Interface::cleanup(void) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->mainWin);
    glfwTerminate();
}