#include "controllers/controller.left_sidebar.hpp"

#include <wx/app.h>
#include <wx/msgdlg.h>
#include <wx/thread.h>

#include "models/model.social_media.hpp"

namespace Controller {

LeftSidebar::LeftSidebar(ViewModel::LeftSidebar* const viewModel) : pViewModel(viewModel) {}

void LeftSidebar::Start() const {
    wxLogDebug("Controller/LeftSidebar: Starting...");
    this->pViewModel->FetchWelcomeText();
}

void LeftSidebar::OnSocialIconTap(Component::SocialContainer::Event& event) {
    const wxString socialMediaUrl = this->GetSocialMediaUrl(event.GetSocialMedia());
    wxLogDebug("Controller/LeftSidebar: Social Icon Tapped: %s. Launching default browser", socialMediaUrl);
    wxLaunchDefaultBrowser(socialMediaUrl);
}

wxString LeftSidebar::GetSocialMediaUrl(const Model::SocialMedia socialMedia) const {
    switch (socialMedia) {
        case Model::SocialMedia::DISCORD:
            return "https://discord.gg/PcjByKk";
        case Model::SocialMedia::REDDIT:
            return "https://reddit.com/r/BTFLgame";
        case Model::SocialMedia::TWITTER:
            return "http://twitter.com/btfl_game";
        case Model::SocialMedia::WEBSITE:
            return "http://btflgame.com";
        case Model::SocialMedia::YOUTUBE:
            return "https://www.youtube.com/channel/UC4Z1YwJ0fAMt5MU0y2melOA/";
    }
}

}  // namespace Controller
