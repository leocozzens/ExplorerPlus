// C++ standard libs
#include <iostream>
#include <cstdlib>
// External libs
#include <GLFW/glfw3.h>
// Local headers
#include <interface.hpp>

#define UTIL_CHECK(_Util, _Failure, _Err) if(!(_Util)) { std::cerr << "ERROR: Failed " << (_Failure) << '\n'; std::exit(_Err); }
#define UTIL_CHECK_TERM(_Util, _Failure, _Termination, _Err) if(!(_Util)) { std::cerr << "ERROR: Failed " << (_Failure) << '\n'; _Termination; std::exit(_Err); }
#define WINDOW_NAME "ExplorerPlus"

Interface::Interface(void) {
    UTIL_CHECK(glfwInit(), "GLFW init", EXIT_FAILURE);
    this->mainWin = glfwCreateWindow(800, 600, WINDOW_NAME, nullptr, nullptr);
    UTIL_CHECK_TERM(this->mainWin, "GLFW window", glfwTerminate(), EXIT_FAILURE);
    glfwMakeContextCurrent(mainWin);
}

void Interface::event_loop(void) {
    while(!glfwWindowShouldClose(this->mainWin)) {
        glfwSwapBuffers(this->mainWin);
        glfwPollEvents();
    }
}

void Interface::cleanup(void) {
    glfwTerminate();
}