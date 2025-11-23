// Local headers
#include <app/interface/frame.hpp>
#include <app/interface/launcher.hpp>

using namespace ExplorerPlus;

bool Launcher::OnInit() {
    m = new MasterFrame("ExplorerPlus");
    m->Show();
    return true;
}