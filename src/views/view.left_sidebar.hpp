#ifndef __VIEW_LEFT_SIDEBAR_HPP__
#define __VIEW_LEFT_SIDEBAR_HPP__

#include <wx/panel.h>

#include "components/component.social_container.hpp"
#include "controllers/controller.left_sidebar.hpp"
#include "view_models/view_model.left_sidebar.hpp"

namespace View {

class LeftSidebar : public wxPanel {
public:
    LeftSidebar(wxWindow *parent, ViewModel::LeftSidebar *viewModel);
    virtual ~LeftSidebar();

private:
    void BindEvents();

private:
    ViewModel::LeftSidebar *const pViewModel;
    Controller::LeftSidebar *const pController;

    Component::SocialContainer *pSocialContainer;

private:
    struct Constants {
        inline static wxSize ViewSize() { return wxSize(400, -1); }
    };
};

}  // namespace View

#endif  // __VIEW_LEFT_SIDEBAR_HPP__
