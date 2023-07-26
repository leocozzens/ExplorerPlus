struct GLFWwindow;

class Interface {
    public:
    Interface(void);
    void event_loop(void);
    void cleanup(void);

    private:
    GLFWwindow *mainWin;
};