#include "views/view.left_sidebar.hpp"

#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>

#include "components/component.read_only_rtc_watcher.hpp"
#include "components/component.social_container.hpp"
#include "controllers/controller.left_sidebar.hpp"
#include "style/style.color.hpp"

namespace View {

LeftSidebar::LeftSidebar(wxWindow* parent, ViewModel::LeftSidebar* viewModel)
    : wxPanel(parent, -1, wxDefaultPosition, Constants::ViewSize()),
      pViewModel(viewModel),
      pController(new Controller::LeftSidebar(pViewModel)) {
    wxLogDebug("View/LeftSidebar: Initializing");
    this->pSocialContainer = new Component::SocialContainer(this);

    wxBoxSizer* const pVerticalSizer = new wxBoxSizer(wxVERTICAL);
    pVerticalSizer->Add(
        new Component::ReadOnlyRTCWatcher(this, &pViewModel->sWelcome),
        wxSizerFlags(1).Expand()
    );
    pVerticalSizer->Add(pSocialContainer, wxSizerFlags().Expand());

    this->SetSizer(pVerticalSizer);
    this->SetMinSize(Constants::ViewSize());
    this->SetBackgroundColour(Style::Color::Black());

    this->BindEvents();

    this->pController->Start();
}

LeftSidebar::~LeftSidebar() {
    delete this->pController;
    delete this->pViewModel;
}

void LeftSidebar::BindEvents() {
    wxLogDebug("View/LeftSidebar: Binding events");
    this->pSocialContainer
        ->Bind(EVT_SOCIAL_CONTAINER, &Controller::LeftSidebar::OnSocialIconTap, this->pController);
}

}  // namespace View
