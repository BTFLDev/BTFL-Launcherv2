#ifndef __STATIC_TEXT_HPP__
#define __STATIC_TEXT_HPP__

#include <wx/stattext.h>

#include "gaze.hpp"

namespace Element {

class StaticTextWatcher : public wxStaticText, public gaze::watcher {
public:
    StaticTextWatcher() {}
    StaticTextWatcher(
        wxWindow* parent,
        wxWindowID id,
        gaze::source<wxString>* label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxASCII_STR(wxStaticTextNameStr)
    ) {
        this->Create(parent, id, label, pos, size, style, name);
    }

    void Create(
        wxWindow* parent,
        wxWindowID id,
        gaze::source<wxString>* label,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxString& name = wxASCII_STR(wxStaticTextNameStr)
    );

protected:
    virtual void subject_updated(const gaze::subject* subj) override;

private:
    gaze::source<wxString>* sLabel;
};

}  // namespace Element

#endif  // __STATIC_TEXT_HPP__
