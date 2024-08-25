#ifndef __MANAGER_SCREEN_HPP__
#define __MANAGER_SCREEN_HPP__

#include <wx/log.h>

#include <gaze.hpp>

#include "models/model.screen.hpp"

namespace Manager {

class Screen {
public:
    Screen(const Screen& other) = delete;

    inline static void SetScreen(Model::Screen screen) {
        Instance().currentScreen.set(screen);
        wxLogDebug("Manager/Screen: Setting active screen to %s", Screen::GetScreenName(screen));
    }
    inline static Model::Screen GetScreen() { return Instance().currentScreen.get(); }

    inline static gaze::source<Model::Screen>* GetScreenSource() {
        return &Instance().currentScreen;
    }

    inline static Screen& Instance() {
        static Screen instance;
        return instance;
    }

private:
    Screen() = default;

    static wxString GetScreenName(Model::Screen screen);

private:
    gaze::source<Model::Screen> currentScreen{Model::Screen::MAIN};
};

}  // namespace Manager

#endif  // __MANAGER_SCREEN_HPP__
