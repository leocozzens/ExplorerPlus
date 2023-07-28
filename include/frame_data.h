#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include <condition_variable>
#define SEARCH_BUFF_SIZE 256

struct _FrameInfo {
    char searchBuff[SEARCH_BUFF_SIZE];
    std::mutex searchLock;
    std::condition_variable searchCheck;
};

#endif