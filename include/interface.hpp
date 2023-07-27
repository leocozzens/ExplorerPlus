struct GLFWwindow;
struct ImGuiIO;
struct ImVec4;

typedef struct {
    int intake;
} FrameInfo;

class Interface {
    public:
    Interface(void);

    void show_frame(FrameInfo *frameData);
    void cleanup(void);

    // Getters
    bool stay_open(void);

    private:
    // Window
    GLFWwindow *mainWin;
    ImGuiIO *io;
    // Colors
    ImVec4 *bgColor;

    static void establish_window_height(int &winWidth, int &winHeight);
    static void set_icon(GLFWwindow *win, const char *filePath);

    void start_glfw(void);
    void start_imgui(void);
};