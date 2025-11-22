// External libraries
#include <wx/wx.h>
// Local headers
#include <app/interface/controller.hpp>

#ifdef RELEASE_BUILD
wxIMPLEMENT_APP(Controller);
#else
wxIMPLEMENT_APP_CONSOLE(Controller);
#endif