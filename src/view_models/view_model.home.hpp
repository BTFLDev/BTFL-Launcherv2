#ifndef __VIEW_MODEL_HOME_HPP__
#define __VIEW_MODEL_HOME_HPP__

#include <wx/font.h>
#include <wx/string.h>

#include <gaze.hpp>

#include "shapes/shape.action_button.hpp"
#include "strings/strings.hpp"

namespace ViewModel {

class Home : public gaze::watcher {
public:
    gaze::source<wxString> mainButtonText{Strings::View::Home::SelectISO(), this};
    gaze::source<Shape::ActionButton::State> mainButtonState{
        Shape::ActionButton::State::IDLE,
        this
    };
    wxFont mainButtonFont{Constants::DefaultMainButtonFont()};

protected:
    void subject_udpated(const gaze::subject* subj) {}

private:
    struct Constants {
        inline static const wxFont DefaultMainButtonFont() {
            return wxFontInfo(20).FaceName("Lora");
        }
    };
};

}  // namespace ViewModel

#endif  // __VIEW_MODEL_HOME_HPP__
