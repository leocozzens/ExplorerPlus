#ifndef INTERFACE_FRAME_HPP
#define INTERFACE_FRAME_HPP

#include <wx/wx.h>
#include <app/interface/widgets.hpp>

namespace ExplorerPlus {
    class MasterFrame : public wxFrame {
        public:
            MasterFrame(const wxString &title);
            ~MasterFrame();
        public:
            wxDECLARE_EVENT_TABLE();
            void button_clicked(wxCommandEvent &evt);
        private:
            static constexpr double frameScale = 0.5;
            static constexpr double get_aspect_ratio(void);

            MainWidgets components;
            void determine_size(int &width, int &height);
    };
}

#endif