#ifndef _COMPONENT_SOCIALCONTAINER_HPP_
#define _COMPONENT_SOCIALCONTAINER_HPP_

#include <wx/panel.h>

#include "elements/element.icon_button.hpp"
#include "models/model.asset.hpp"
#include "models/model.social_media.hpp"

namespace Component {

class SocialContainer : public wxPanel {
public:
    class Event : public wxCommandEvent {
    public:
        Event() {}
        Event(wxWindowID id, Model::SocialMedia socialMedia);

        void SetSocialMedia(Model::SocialMedia socialMedia);
        Model::SocialMedia GetSocialMedia();

    private:
        Model::SocialMedia socialMedia;
    };

public:
    SocialContainer(wxWindow* parent);

private:
    Model::Asset::Icon GetSocialMediaIcon(Model::SocialMedia socialMedia);
    Model::SocialMedia GetSocialMedia(Model::Asset::Icon  socialMedia);

    void OnIconButton(Element::IconButton::Event& event);

private:
    struct Constants {
        inline static int HorizontalSpacing() { return 24; }
    };
};

}  // namespace Component

wxDECLARE_EVENT(EVT_SOCIAL_CONTAINER, Component::SocialContainer::Event);

#endif  // _COMPONENT_SOCIALCONTAINER_HPP_
