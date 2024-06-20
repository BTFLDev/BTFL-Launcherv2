#include "controllers/controller.footer_main.hpp"

#include <wx/msgdlg.h>

#include "managers/manager.screen.hpp"

namespace Controller {

void FooterMain::OnReadDisclaimerTapped(wxCommandEvent& event) {
    Manager::Screen::SetScreen(Model::Screen::SECONDARY);
}

}  // namespace Controller
