#ifndef __SHAPE_TEXT_WATCHER_HPP__
#define __SHAPE_TEXT_WATCHER_HPP__

#include <wx/wxsf/DiagramManager.h>
#include <wx/wxsf/TextShape.h>

#include <gaze.hpp>

#include "shapes/shape.pinner.hpp"

namespace Shape {

class TextWatcher : public wxSFTextShape, public gaze::watcher, public Shape::Pinner {
public:
    TextWatcher();
    TextWatcher(const TextWatcher& other);
    TextWatcher(const wxRealPoint& pos, gaze::source<wxString>* text, wxSFDiagramManager* manager);

public:  // Pinner implementation
    inline virtual void MoveTo(const wxRealPoint& point) override {
        wxSFTextShape::MoveTo(point.x, point.y);
    }
    inline virtual wxRealPoint GetPosition() override {
        return wxSFTextShape::GetAbsolutePosition();
    }
    inline virtual wxRealPoint GetSize() override { return this->GetRectSize(); }

protected:
    void subject_updated(const gaze::subject* subj) override;

private:
    gaze::source<wxString>* text{nullptr};
};

}  // namespace Shape

#endif
