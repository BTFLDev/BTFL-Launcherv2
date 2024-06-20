#ifndef __SCREEN_LAUNCHER_MAIN_HPP__
#define __SCREEN_LAUNCHER_MAIN_HPP__

#include <wx/panel.h>

#include <gaze.hpp>

namespace Screen {

class LauncherMain : public wxPanel {
public:
    LauncherMain() = default;
    LauncherMain(wxWindow* parent) { this->Create(parent); }

    void Create(wxWindow* parent);
};

}  // namespace Screen

#endif  // __SCREEN_LAUNCHER_MAIN_HPP__
