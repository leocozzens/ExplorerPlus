#ifndef TASK_HANDLER_HPP
#define TASK_HANDLER_HPP

typedef struct _FrameInfo FrameInfo;

class TaskHandler {
    public:
        TaskHandler(FrameInfo *frameData);
    private:
        // External data
        FrameInfo *frameData;

        void handle_search(void);
        void run_search(const char *searchQuery, size_t querySize);
};

#endif