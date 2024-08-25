#include "managers/manager.screen.hpp"

namespace Manager {

wxString Screen::GetScreenName(Model::Screen screen) {
    switch (screen) {
        case Model::Screen::MAIN:
            return "MAIN";
        case Model::Screen::SECONDARY:
            return "SECONDARY";
    }
};

}  // namespace Manager
