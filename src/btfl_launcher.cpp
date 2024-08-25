#include "btfl_launcher.hpp"

#include <wx/msgdlg.h>
#include <wx/nonownedwnd.h>
#include <wx/region.h>
#include <wx/stdpaths.h>
#include <wx/toplevel.h>
#include <cstdlib>

#include "managers/manager.asset.hpp"
#include "managers/manager.screen.hpp"
#include "strings/strings.hpp"
#include "style/style.color.hpp"

wxIMPLEMENT_APP(BTFLLauncher);

bool BTFLLauncher::OnInit() {
    this->SetupManagers();

    wxLogDebug("Initializing srand with current time seed");
    std::srand(std::time(nullptr));

    // wxFileName fontPath = Manager::Asset::GetAssetsPath();
    // fontPath.AppendDir("Fonts");
    // fontPath.SetName("Lora-Regular.ttf");
    // wxFont::AddPrivateFont(fontPath.GetFullPath()); // why isn't this working??

    wxBitmap frameShape = Manager::Asset::GetShape(Model::Asset::Shape::MAIN_FRAME);
    this->pAppFrame = new Frame::AppMain(
        Strings::Frame::AppMain::Title(),
        frameShape.GetSize(),
        wxFRAME_SHAPED | wxBORDER_NONE
    );
    this->pAppFrame->Hide();
    wxLogDebug("Setting App Frame to bitmap shape for rounded corners");
    this->pAppFrame->SetShape(wxRegion(frameShape, Style::Color::White()));
    this->pAppFrame->CenterOnScreen();
    this->pAppFrame->Layout();
    this->pAppFrame->Update();

    Manager::Screen::SetScreen(Model::Screen::MAIN);
    this->pAppFrame->Show();

    return true;
}

int BTFLLauncher::OnExit() { return wxApp::OnExit(); }

void BTFLLauncher::SetupManagers() {
    Manager::Asset::SetAssetsPath(wxStandardPaths::Get().GetResourcesDir());
}
