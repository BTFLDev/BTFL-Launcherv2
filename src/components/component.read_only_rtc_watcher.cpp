#include "components/component.read_only_rtc_watcher.hpp"

#include <wx/richtext/richtextbuffer.h>
#include <wx/sstream.h>

#include "components/component.read_only_rtc.hpp"

namespace Component {

void ReadOnlyRTCWatcher::Create(wxWindow* parent, gaze::source<wxString>* value) {
    ReadOnlyRTC::Create(parent, value->get());

    this->sValue = this->watch_assign(value);
}

void ReadOnlyRTCWatcher::subject_updated(const gaze::subject* subj) {
    this->CallAfter([this, subj]() {
        if (subj == this->sValue) {
            wxStringInputStream stream{this->sValue->get()};
            this->GetBuffer().LoadFile(stream, wxRICHTEXT_TYPE_TEXT);
            this->Update();
            this->Refresh();
        }
    });
}

}  // namespace Component
