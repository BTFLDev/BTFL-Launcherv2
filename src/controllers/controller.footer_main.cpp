#include "controllers/controller.footer_main.hpp"

#include <wx/msgdlg.h>

#include "managers/manager.screen.hpp"

namespace Controller {

void FooterMain::OnReadDisclaimerTapped(wxCommandEvent& event) {
    wxLogDebug("Controller/FooterMain: Read Disclaimer button tapped");
    Manager::Screen::SetScreen(Model::Screen::SECONDARY);
}

}  // namespace Controller
