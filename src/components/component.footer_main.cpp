#include "components/component.footer_main.hpp"

#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

#include "elements/element.text_button.hpp"
#include "strings/strings.hpp"
#include "style/style.color.hpp"
#include "style/style.spacing.hpp"

namespace Component {

FooterMain::~FooterMain() {
    if (this->pController != nullptr) {
        delete this->pController;
    }
}

void FooterMain::Create(wxWindow* parent) {
    wxLogDebug("Component/FooterMain: Initializing");
    wxPanel::Create(parent);

    this->pController = new Controller::FooterMain();

    wxStaticText* pFooterText = new wxStaticText(
        this,
        -1,
        Strings::Screen::LauncherMain::Footer(),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_LEFT | wxST_ELLIPSIZE_END
    );
    pFooterText->SetForegroundColour(Style::Color::TextDarkGrey());

    this->pReadDisclaimerButton =
        new Element::TextButton(this, -1, Strings::Screen::LauncherMain::ReadDisclaimer());
    this->pReadDisclaimerButton->SetForegroundColour(Style::Color::Turquoise());

    wxBoxSizer* pFooterSizer = new wxBoxSizer(wxHORIZONTAL);
    pFooterSizer->Add(pFooterText, wxSizerFlags(1).Border(wxTOP | wxBOTTOM, Style::Spacing::S12()));
    pFooterSizer->AddSpacer(Style::Spacing::S24());
    pFooterSizer->Add(
        this->pReadDisclaimerButton,
        wxSizerFlags().Border(wxTOP | wxBOTTOM, Style::Spacing::S12())
    );

    this->SetSizer(pFooterSizer);
    this->SetBackgroundColour(Style::Color::Black());

    this->BindEvents();
}

void FooterMain::BindEvents() {
    wxLogDebug("Component/FooterMain: Binding events");
    this->pReadDisclaimerButton
        ->Bind(wxEVT_BUTTON, &Controller::FooterMain::OnReadDisclaimerTapped, this->pController);
}

}  // namespace Component
