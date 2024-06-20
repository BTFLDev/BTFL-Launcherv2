#include "view_models/view_model.left_sidebar.hpp"

#include <chrono>
#include <thread>

namespace ViewModel {

void LeftSidebar::FetchWelcomeText() {
    std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->sWelcome.set("Loading 5...");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->sWelcome.set("Loading 4...");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->sWelcome.set("Loading 3...");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->sWelcome.set("Loading 2...");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->sWelcome.set("Loading 1...");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->sWelcome.set("Empty for now, but later on this'll fetch the release notes and whatnot"
        );
    }).detach();
}
}  // namespace ViewModel
