// Standard headers
#include <iostream>
// External libraries
#include <wx/display.h>
// Local headers
#include <app/interface/frame.hpp>

#define PRIMARY_DISPLAY 0

using namespace ExplorerPlus;

wxBEGIN_EVENT_TABLE(MasterFrame, wxFrame)
wxEND_EVENT_TABLE()

MasterFrame::MasterFrame(const wxString &title):
    wxFrame(nullptr, wxID_ANY, title),
    components(this)
{
    int width, height;
    determine_size(width, height);
    SetSize(width, height);
    Center();

    components.button.Bind(
        wxEVT_COMMAND_BUTTON_CLICKED,
        &MasterFrame::button_clicked,
        this
    );
}

MasterFrame::~MasterFrame(void) {

}

// Public

void MasterFrame::button_clicked(wxCommandEvent &evt) {
    std::cout << "Clicked primary button" << std::endl;
    components.list.Append(components.txt.GetValue());
    evt.Skip();
}

// Private

constexpr double MasterFrame::get_aspect_ratio(void) {
    return (16.0 / 9.0);
}

void MasterFrame::determine_size(int &width, int &height) {
    int displayIndex = wxDisplay::GetFromWindow(this);
    if(displayIndex == wxNOT_FOUND) displayIndex = PRIMARY_DISPLAY;

    wxDisplay display(displayIndex);
    wxRect screenSize = display.GetClientArea();
    width = screenSize.GetWidth() * frameScale;
    height = (int) (width / get_aspect_ratio());

    if(height > screenSize.GetHeight()) {
        height = screenSize.GetHeight() * frameScale;
        width = (int) (height * get_aspect_ratio());
    }
}