// Local headers
#include <app/interface/widgets.hpp>

using namespace ExplorerPlus;

MainWidgets::MainWidgets(wxFrame *target) {
    this->button.Create(target, wxID_ANY, "Click me", wxPoint(10, 10), wxSize(150, 50));
    this->txt.Create(target, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
    this->list.Create(target, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}