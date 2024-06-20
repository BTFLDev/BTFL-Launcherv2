#include "frames/frame.app_main.hpp"

#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/simplebook.h>
#include <wx/sizer.h>
#include <wx/toplevel.h>

#include "managers/manager.screen.hpp"
#include "screens/screen.launcher_main.hpp"
#include "screens/screen.launcher_secondary.hpp"
#include "style/style.color.hpp"

namespace Frame {

void AppMain::Create(const wxString& title, const wxSize& size, long style) {
    wxFrame::Create(nullptr, -1, title, wxDefaultPosition, size, style);

    this->pBook = new wxSimplebook(this);
    this->pBook->ShowNewPage(new Screen::LauncherMain(this->pBook));
    this->pBook->ShowNewPage(new Screen::LauncherSecondary(this->pBook, new wxSFDiagramManager));

    wxBoxSizer* pSizer = new wxBoxSizer(wxHORIZONTAL);
    pSizer->Add(this->pBook, wxSizerFlags(1).Expand());

    this->SetSizer(pSizer);
    this->SetBackgroundColour(Style::Color::Black());
    this->SetMenuBar(new wxMenuBar());

    this->BindEvents();

    this->watch(Manager::Screen::GetScreenSource());
}

void AppMain::BindEvents() {}

void AppMain::subject_updated(const gaze::subject* subj) {
    this->CallAfter([this, subj]() {
        if (subj == Manager::Screen::GetScreenSource()) {
            this->pBook->SetSelection(size_t(Manager::Screen::GetScreen()));
        }
    });
}

}  // namespace Frame
