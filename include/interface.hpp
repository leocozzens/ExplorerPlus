struct GLFWwindow;
struct ImGuiIO;

class Interface {
    public:
    Interface(void);
    static void establish_window_height(int &winWidth, int &winHeight);

    void event_loop(void);
    void cleanup(void);

    private:
    GLFWwindow *mainWin;
    ImGuiIO *io;
};