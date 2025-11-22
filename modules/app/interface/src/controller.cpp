// External Libraries
#include <wx/wx.h>
// Local headers
#include <app/interface/frame.hpp>
#include <app/interface/controller.hpp>

bool Controller::OnInit() {
    this->m = new MasterFrame("C++ GUI Demo");
    m->Show();
    return true;
}