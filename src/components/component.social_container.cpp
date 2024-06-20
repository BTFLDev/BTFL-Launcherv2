#include "components/component.social_container.hpp"

#include <wx/msgdlg.h>
#include <wx/sizer.h>

#include "components/component.divider.hpp"
#include "elements/element.icon_button.hpp"
#include "models/model.social_media.hpp"
#include "style/style.color.hpp"
#include "style/style.spacing.hpp"

wxDEFINE_EVENT(EVT_SOCIAL_CONTAINER, Component::SocialContainer::Event);

namespace Component {

SocialContainer::Event::Event(wxWindowID id, Model::SocialMedia socialMedia)
    : wxCommandEvent(EVT_SOCIAL_CONTAINER, id), socialMedia(socialMedia) {}

Model::SocialMedia SocialContainer::Event::GetSocialMedia() { return this->socialMedia; }

void SocialContainer::Event::SetSocialMedia(Model::SocialMedia socialMedia) {
    this->socialMedia = socialMedia;
}

SocialContainer::SocialContainer(wxWindow* parent) : wxPanel(parent) {
    wxBoxSizer* pHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);

    for (const Model::SocialMedia& socialMedia : Model::AllSocialMediaCases()) {
        Element::IconButton* pButton =
            new Element::IconButton(this, this->GetSocialMediaIcon(socialMedia));
        pButton->Bind(EVT_ICON_BUTTON, &SocialContainer::OnIconButton, this);
        pHorizontalSizer->Add(
            pButton,
            wxSizerFlags().Center().Border(wxLEFT | wxRIGHT, Style::Spacing::S12())
        );
    }

    wxBoxSizer* pVerticalSizer = new wxBoxSizer(wxVERTICAL);
    pVerticalSizer->Add(new Component::Divider(this), wxSizerFlags().Expand());
    pVerticalSizer->Add(
        pHorizontalSizer,
        wxSizerFlags().CenterHorizontal().Border(wxBOTTOM | wxTOP, Style::Spacing::S16())
    );
    pVerticalSizer->Add(new Component::Divider(this), wxSizerFlags().Expand());

    this->SetSizer(pVerticalSizer);
    this->SetBackgroundColour(Style::Color::Black());
}

Model::Asset::Icon SocialContainer::GetSocialMediaIcon(Model::SocialMedia socialMedia) {
    switch (socialMedia) {
        case Model::SocialMedia::DISCORD:
            return Model::Asset::Icon::DISCORD;
        case Model::SocialMedia::REDDIT:
            return Model::Asset::Icon::REDDIT;
        case Model::SocialMedia::TWITTER:
            return Model::Asset::Icon::TWITTER;
        case Model::SocialMedia::WEBSITE:
            return Model::Asset::Icon::WEBSITE;
        case Model::SocialMedia::YOUTUBE:
            return Model::Asset::Icon::YOUTUBE;
    }
}

Model::SocialMedia SocialContainer::GetSocialMedia(Model::Asset::Icon socialMedia) {
    switch (socialMedia) {
        case Model::Asset::Icon::DISCORD:
            return Model::SocialMedia::DISCORD;
        case Model::Asset::Icon::REDDIT:
            return Model::SocialMedia::REDDIT;
        case Model::Asset::Icon::TWITTER:
            return Model::SocialMedia::TWITTER;
        case Model::Asset::Icon::WEBSITE:
            return Model::SocialMedia::WEBSITE;
        case Model::Asset::Icon::YOUTUBE:
            return Model::SocialMedia::YOUTUBE;
    }
}

void Component::SocialContainer::OnIconButton(Element::IconButton::Event& event) {
    Model::SocialMedia socialMedia = this->GetSocialMedia(event.GetIcon());

    Event socialEvent{this->GetId(), socialMedia};
    socialEvent.SetEventObject(this);
    this->ProcessEvent(socialEvent);
}

}  // namespace Component
