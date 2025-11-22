#ifndef INTERFACE_CONTROLLER_HPP
#define INTERFACE_CONTROLLER_HPP

#include <wx/app.h>

namespace ExplorerPlus {
    class MasterFrame;

    class Launcher : public wxApp {
        public:
            bool OnInit();
        private:
            MasterFrame *m;
    };
}

#endif