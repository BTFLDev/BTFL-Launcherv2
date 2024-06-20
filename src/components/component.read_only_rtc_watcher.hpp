#ifndef __READ_ONLY_RTC_WATCHER_HPP__
#define __READ_ONLY_RTC_WATCHER_HPP__

#include <wx/bmpbndl.h>
#include <wx/richtext/richtextctrl.h>

#include <gaze.hpp>

#include "components/component.read_only_rtc.hpp"

namespace Component {

class ReadOnlyRTCWatcher : public ReadOnlyRTC, public gaze::watcher {
public:
    ReadOnlyRTCWatcher() {}
    ReadOnlyRTCWatcher(wxWindow* parent, gaze::source<wxString>* value) {
        this->Create(parent, value);
    }

    void Create(wxWindow* parent, gaze::source<wxString>* value);

protected:
    virtual void subject_updated(const gaze::subject* subj);

private:
    gaze::source<wxString>* sValue;
};

}  // namespace Component

#endif  // __READ_ONLY_RTC_WATCHER_HPP__
