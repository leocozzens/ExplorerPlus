// Local headers
#include <app/interface/widgets.hpp>

using namespace ExplorerPlus;

MainWidgets::MainWidgets(wxFrame *target) {
    button.Create(target, wxID_ANY, "Click me", wxPoint(10, 10), wxSize(150, 50));
    txt.Create(target, wxID_ANY, "Test 123", wxPoint(10, 70), wxSize(300, 30));
    list.Create(target, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}