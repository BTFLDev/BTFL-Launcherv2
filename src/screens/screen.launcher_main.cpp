#include "screens/screen.launcher_main.hpp"

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

#include "components/component.footer_main.hpp"
#include "style/style.color.hpp"
#include "style/style.spacing.hpp"
#include "views/view.home.hpp"
#include "views/view.left_sidebar.hpp"

namespace Screen {

void LauncherMain::Create(wxWindow* parent) {
    wxPanel::Create(parent);

    wxBoxSizer* pHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    pHorizontalSizer->Add(
        new View::LeftSidebar(this, new ViewModel::LeftSidebar()),
        wxSizerFlags(0).Expand()
    );
    pHorizontalSizer->Add(
        new View::Home(this, new wxSFDiagramManager, new ViewModel::Home),
        wxSizerFlags(1).Expand()
    );

    wxBoxSizer* pVerticalSizer = new wxBoxSizer(wxVERTICAL);
    pVerticalSizer->Add(pHorizontalSizer, wxSizerFlags(1).Expand());
    pVerticalSizer->Add(
        new Component::FooterMain(this),
        wxSizerFlags().Expand().Border(wxLEFT | wxRIGHT, Style::Spacing::S24())
    );

    this->SetSizer(pVerticalSizer);
    this->SetBackgroundColour(Style::Color::Black());
}

}  // namespace Screen
