#ifndef INTERFACE_LAUNCHER_HPP
#define INTERFACE_LAUNCHER_HPP

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