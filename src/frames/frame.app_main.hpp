#ifndef __FRAME_APP_MAIN_HPP__
#define __FRAME_APP_MAIN_HPP__

#include <wx/frame.h>
#include <wx/simplebook.h>

#include <gaze.hpp>

namespace Frame {

class AppMain : public wxFrame, public gaze::watcher {
public:
    AppMain() {}
    AppMain(const wxString& title, const wxSize& size, long style) {
        this->Create(title, size, style);
    }

private:
    void Create(const wxString& title, const wxSize& size, long style);

    void BindEvents();

    virtual void subject_updated(const gaze::subject* subj) override;

private:
    wxSimplebook* pBook{nullptr};

private:
    struct Constants {
        inline static const wxSize DefaultSize() { return {1280, 720}; }
    };
};

}  // namespace Frame

#endif  // __FRAME_APP_MAIN_HPP__
