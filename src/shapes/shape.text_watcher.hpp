#ifndef __SHAPE_TEXT_WATCHER_HPP__
#define __SHAPE_TEXT_WATCHER_HPP__

#include <gaze.hpp>

#include "wx/wxsf/DiagramManager.h"
#include "wx/wxsf/TextShape.h"

namespace Shape {

class TextWatcher : public wxSFTextShape, public gaze::watcher {
public:
    TextWatcher();
    TextWatcher(const TextWatcher& other);
    TextWatcher(const wxRealPoint& pos, gaze::source<wxString>* text, wxSFDiagramManager* manager);

protected:
    void subject_updated(const gaze::subject* subj) override;

private:
    gaze::source<wxString>* text{nullptr};
};

}  // namespace Shape

#endif
