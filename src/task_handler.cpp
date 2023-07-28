// C++ standard libraries
#include <iostream>
#include <cstring>
#include <thread>
// Local headers
#include <frame_data.h>
#include <task_handler.hpp>

// Constructor/Destructor
TaskHandler::TaskHandler(FrameInfo *frameData) {
    this->frameData = frameData;
    std::thread searchLoop(&handle_search, this);
    searchLoop.detach();
}

// Instance function
void TaskHandler::handle_search(void) {
    while(true) {
        char searchQuery[SEARCH_BUFF_SIZE];
        bool shouldSearch = false;

        std::unique_lock<std::mutex> searchLock(this->frameData->searchLock);
        this->frameData->searchCheck.wait(searchLock);

        if(this->frameData->searchBuff[0] != '\0') shouldSearch = true;
        if(shouldSearch) strncpy(searchQuery, this->frameData->searchBuff, sizeof(searchQuery));

        this->frameData->searchCheck.notify_one();
        searchLock.unlock();
        if(shouldSearch) run_search(searchQuery, sizeof(searchQuery));
    }
}


void TaskHandler::run_search(const char *searchQuery, size_t querySize) {
    std::cout.write(searchQuery, querySize);
    std::cout << std::endl;
}