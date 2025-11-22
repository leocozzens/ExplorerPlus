#ifndef INTERFACE_FRAME_HPP
#define INTERFACE_FRAME_HPP

#include <wx/wx.h>
#include <app/interface/widgets.hpp>

namespace ExplorerPlus {
    class MasterFrame : public wxFrame {
        public:
            MasterFrame(const wxString &title);
            ~MasterFrame(void);
        public:
            wxDECLARE_EVENT_TABLE();
            void button_clicked(wxCommandEvent &evt);
        private:
            MainWidgets components;
    };
}

#endif