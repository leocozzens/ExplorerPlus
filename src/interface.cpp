// C++ standard libs
#include <iostream>
#include <cstdlib>
// External libs
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> // TODO: Replace with custom tool

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// Local headers
#include <interface.hpp>


#define UTIL_CHECK(_Util, _Failure, _Err) if(!(_Util)) { std::cerr << "ERROR: Failed " << (_Failure) << '\n'; std::exit(_Err); }
#define UTIL_CHECK_TERM(_Util, _Failure, _Termination, _Err) if((_Util) == nullptr) { std::cerr << "ERROR: Failed " << (_Failure) << '\n'; _Termination; std::exit(_Err); }

#define WINDOW_NAME "ExplorerPlus"
#define WIDTH_ASPECT 0.55F
#define HEIGHT_ASPECT 0.45F
#define IMGUI_ENABLE_CALLBACKS true
// #define ENABLE_MERGE
// #define DISABLE_DOCKING
// #define LIGHT_ENABLE

// Constructor/Destructor
Interface::Interface(void) {
    this->start_glfw();
    this->start_imgui();
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

void Interface::set_icon(GLFWwindow *win) {
    int imgWidth, imgHeight, channels;
    unsigned char *pixels = stbi_load("assets/images/icon.png", &imgWidth, &imgHeight, &channels, 4);
    GLFWimage images[1];
    images[0].width = imgWidth;
    images[0].height = imgHeight;
    images[0].pixels = pixels;
    glfwSetWindowIcon(win, 1, images);
}

// Instance methods
void Interface::start_glfw(void) {
    UTIL_CHECK(glfwInit(), "GLFW init", EXIT_FAILURE);
    int winWidth, winHeight;
    establish_window_height(winWidth, winHeight);
    this->mainWin = glfwCreateWindow(winWidth, winHeight, WINDOW_NAME, nullptr, nullptr);
    UTIL_CHECK_TERM(this->mainWin, "GLFW window", glfwTerminate(), EXIT_FAILURE);
    glfwMakeContextCurrent(this->mainWin);
    glfwSwapInterval(1); // Enable vsync
    set_icon(this->mainWin);
}

void Interface::start_imgui(void) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    this->io = &(ImGui::GetIO());
    this->io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    this->io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    #ifndef DISABLE_DOCKING
    this->io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    this->io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    // Tweak auxiliary viewports
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 0.0F;
    style.Colors[ImGuiCol_WindowBg].w = 1.0F;
    #endif
    #ifndef ENABLE_MERGE // Allow imgui to render windows together if their viewports are contained within the parent
    this->io->ConfigViewportsNoAutoMerge = true;
    #endif
    this->io->ConfigViewportsNoTaskBarIcon = true; // Auxiliary windows will not show on taskbar

    #ifndef LIGHT_ENABLE
    ImGui::StyleColorsDark();
    this->bgColor = new ImVec4(1.00F, 1.00F, 1.00F, 0.12F);
    #else
    ImGui::StyleColorsLight();
    this->bgColor = ImVec4(1.00F, 1.00F, 1.00F, 0.90F);
    #endif

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->mainWin, IMGUI_ENABLE_CALLBACKS);
    ImGui_ImplOpenGL3_Init();
}

void Interface::show_frame(FrameInfo *frameData) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(this->mainWin, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(this->bgColor->x * this->bgColor->w, this->bgColor->y * this->bgColor->w, this->bgColor->z * this->bgColor->w, this->bgColor->w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    #ifndef DISABLE_DOCKING
    if (this->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
    #endif

    glfwSwapBuffers(this->mainWin);
}

void Interface::cleanup(void) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->mainWin);
    glfwTerminate();

    delete this->bgColor;
}

// Getters
bool Interface::stay_open(void) {
    return !glfwWindowShouldClose(this->mainWin);
}