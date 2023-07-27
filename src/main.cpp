// Local headers
#include <interface.hpp>

int main(void) {
    Interface display;
    FrameInfo frameData { 1 };
    while(display.stay_open()) {
        display.show_frame(&frameData);
    }
    display.cleanup();

    return 0;
}