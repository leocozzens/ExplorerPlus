// External libraries
#include <wx/wx.h>
// Local headers
#include <app/interface/launcher.hpp>

#ifdef RELEASE_BUILD
wxIMPLEMENT_APP(Launcher);
#else
wxIMPLEMENT_APP_CONSOLE(Launcher);
#endif