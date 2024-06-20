#ifndef __VIEW_MODEL_LEFT_SIDEBAR_HPP__
#define __VIEW_MODEL_LEFT_SIDEBAR_HPP__

#include <wx/string.h>

#include "gaze.hpp"

namespace ViewModel {

class LeftSidebar : public gaze::watcher {
public:
    gaze::source<wxString> sWelcome{"", this};
    gaze::source<wxString> sPatchNotes{"", this};

    void FetchWelcomeText();
};

}  // namespace ViewModel

#endif  // __VIEW_MODEL_LEFT_SIDEBAR_HPP__
