// Standard headers
#include <iostream>
// Local headers
#include <app/interface/frame.hpp>

using namespace ExplorerPlus;

wxBEGIN_EVENT_TABLE(MasterFrame, wxFrame)
wxEND_EVENT_TABLE()

MasterFrame::MasterFrame(const wxString &title):
    wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),
    components(this)
{
    components.button.Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MasterFrame::button_clicked, this);
}

MasterFrame::~MasterFrame(void) {

}

void MasterFrame::button_clicked(wxCommandEvent &evt) {
    std::cout << "Clicked primary button" << std::endl;
    components.list.Append(components.txt.GetValue());
    evt.Skip();
}