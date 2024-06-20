#ifndef __SCREEN_LAUNCHER_SECONDARY_HPP__
#define __SCREEN_LAUNCHER_SECONDARY_HPP__

#include <wx/panel.h>

#include <gaze.hpp>

#include "utils/background_image_canvas.hpp"

namespace Screen {

class LauncherSecondary : public Utils::BackgroundImageCanvas {
public:
    LauncherSecondary(wxWindow* parent, wxSFDiagramManager* manager) {
        this->Create(parent, manager);
    }

private:
    void Create(wxWindow* parent, wxSFDiagramManager* manager);
};

}  // namespace Screen

#endif  // __SCREEN_LAUNCHER_SECONDARY_HPP__
