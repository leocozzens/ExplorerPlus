#ifndef INTERFACE_WIDGETS_HPP
#define INTERFACE_WIDGETS_HPP

#include <wx/wx.h>

namespace ExplorerPlus {
    class MainWidgets {
        public:
            MainWidgets(wxFrame *target);
            wxButton button;
            wxTextCtrl txt;
            wxListBox list;
    };
}

#endif