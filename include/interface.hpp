#ifndef INTERFACE_HPP
#define INTERFACE_HPP

typedef struct _FrameInfo FrameInfo;

struct GLFWwindow;
struct ImGuiIO;
struct ImVec4;

class Interface {
    public:
    Interface(FrameInfo *frameData);

    void show_frame(void);
    void cleanup(void);

    // Getters
    bool stay_open(void);

    private:
    // Window
    GLFWwindow *mainWin;
    ImGuiIO *io;
    // Colors
    ImVec4 *bgColor;
    // External data
    FrameInfo *frameData;

    static void establish_window_height(int &winWidth, int &winHeight);
    static void set_icon(GLFWwindow *win, const char *filePath);
    static void new_frame(void);

    void start_glfw(void);
    void start_imgui(void);
    void render_viewport(void);
    void set_internals(void);
};

#endif