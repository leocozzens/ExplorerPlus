// Local headers
#include <frame_data.h>
#include <interface.hpp>
#include <task_handler.hpp>

int main(void) {
    FrameInfo frameData;
    Interface display(&frameData);
    TaskHandler handler(&frameData);
    while(display.stay_open()) {
        display.show_frame();
    }
    display.cleanup();
    return 0;
}