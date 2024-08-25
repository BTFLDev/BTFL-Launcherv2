#ifndef __VIEW_MODEL_HOME_HPP__
#define __VIEW_MODEL_HOME_HPP__

#include <wx/font.h>
#include <wx/string.h>

#include <gaze.hpp>

#include "managers/manager.asset.hpp"
#include "models/model.asset.hpp"
#include "shapes/shape.action_button.hpp"
#include "shapes/shape.iso_info.hpp"
#include "strings/strings.hpp"
#include "style/style.spacing.hpp"

namespace ViewModel {

class Home : public gaze::watcher {
public:
    gaze::source<wxString> mainButtonText{Strings::View::Home::SelectISO(), this};
    gaze::source<Shape::ActionButton::State> mainButtonState{
        Shape::ActionButton::State::IDLE,
        this
    };
    wxFont mainButtonFont{Constants::DefaultMainButtonFont()};

    gaze::source<wxString> settingsButtonText{wxString(), this};
    gaze::source<wxBitmapBundle> settingsButtonIcon{
        Manager::Asset::GetIcon(Model::Asset::Icon::REDDIT, {32, 32}),
        this
    };
    gaze::source<int> settingsButtonYPadding{Style::Spacing::S16()};
    gaze::source<int> settingsButtonXPadding{Style::Spacing::S16()};
    gaze::source<Shape::ActionButton::State> settingsButtonState{
        Shape::ActionButton::State::IDLE,
        this
    };
    wxFont settingsButtonFont{Constants::DefaultMainButtonFont()};

    gaze::source<wxString> isoFile{"testing", this};
    gaze::source<Shape::ISOInfo::State> isoState{Shape::ISOInfo::State::TO_SELECT_ISO, this};

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
