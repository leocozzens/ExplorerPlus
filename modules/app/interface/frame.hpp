#ifndef INTERFACE_FRAME_HPP

#include <wx/frame.h>
#include <app/interface/widgets.hpp>

class MasterFrame : public wxFrame {
    public:
        MasterFrame(const wxString &title);
        ~MasterFrame(void);
    private:
        MainWidgets components;
};

#endif