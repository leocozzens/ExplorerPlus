// Local headers
#include <interface.hpp>

int main(void) {
    Interface display;
    display.event_loop();
    display.cleanup();

    return 0;
}