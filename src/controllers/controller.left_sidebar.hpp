#ifndef __CONTROLLER_LEFT_SIDEBAR_HPP__
#define __CONTROLLER_LEFT_SIDEBAR_HPP__

#include <wx/event.h>

#include "components/component.social_container.hpp"
#include "models/model.social_media.hpp"
#include "view_models/view_model.left_sidebar.hpp"

namespace Controller {

class LeftSidebar {
public:
    LeftSidebar(ViewModel::LeftSidebar *const viewModel);

    void Start() const;

    void OnSocialIconTap(Component::SocialContainer::Event &event);

private:
    wxString GetSocialMediaUrl(const Model::SocialMedia socialMedia) const;

private:
    ViewModel::LeftSidebar *const pViewModel;
};

}  // namespace Controller

#endif  // __CONTROLLER_LEFT_SIDEBAR_HPP__
