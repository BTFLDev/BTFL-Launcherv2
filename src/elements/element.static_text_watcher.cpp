#include "elements/element.static_text_watcher.hpp"

#include <wx/msgdlg.h>

#include "gaze.hpp"

namespace Element {

void StaticTextWatcher::Create(
    wxWindow* parent,
    wxWindowID id,
    gaze::source<wxString>* label,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name
) {
    wxStaticText::Create(parent, id, label->get(), pos, size, style, name);
    this->sLabel = this->watch_assign(label);
}

void StaticTextWatcher::subject_updated(const gaze::subject* subj) {
    this->CallAfter([this, subj]() {
        if (subj == this->sLabel) {
            this->SetLabel(this->sLabel->get());
            this->Layout();
            this->Update();
            this->Refresh();
        }
    });
}

}  // namespace Element
