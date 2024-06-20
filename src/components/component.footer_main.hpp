#ifndef __SCREEN_FOOTER_MAIN_HPP__
#define __SCREEN_FOOTER_MAIN_HPP__

#include <wx/panel.h>

#include <gaze.hpp>

#include "controllers/controller.footer_main.hpp"
#include "elements/element.text_button.hpp"

namespace Component {

class FooterMain : public wxPanel {
public:
    FooterMain() {}
    FooterMain(wxWindow* parent) {
        this->Create(parent);
    }
    virtual ~FooterMain();

    void Create(wxWindow* parent);

private:
    void BindEvents();

private:
    Controller::FooterMain* pController{nullptr};

    Element::TextButton* pReadDisclaimerButton{nullptr};
};

}  // namespace Component

#endif  // __SCREEN_FOOTER_MAIN_HPP__
