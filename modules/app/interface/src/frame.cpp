// External libraries
#include <wx/wx.h>
// Local headers
#include <app/interface/frame.hpp>

MasterFrame::MasterFrame(const wxString &title):
    wxFrame(nullptr, wxID_ANY, title),
    components(this)
{
    
}

MasterFrame::~MasterFrame(void) {

}