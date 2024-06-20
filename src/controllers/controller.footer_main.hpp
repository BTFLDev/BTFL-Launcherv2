#ifndef __CONTROLLER_FOOTER_MAIN_HPP__
#define __CONTROLLER_FOOTER_MAIN_HPP__

#include <wx/event.h>

#include <gaze.hpp>

namespace Controller {

class FooterMain {
public:
    void OnReadDisclaimerTapped(wxCommandEvent& event);
};

}  // namespace Controller

#endif  // __CONTROLLER_FOOTER_MAIN_HPP__
