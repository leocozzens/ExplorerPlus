#ifndef INTERFACE_CONTROLLER_HPP

#include <wx/app.h>

class MasterFrame;

class Controller : public wxApp {
    public:
        bool OnInit();
    private:
        MasterFrame *m;
};

#endif