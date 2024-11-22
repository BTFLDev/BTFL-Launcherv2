#ifndef __SHAPE_BITMAP_WATCHER_HPP__
#define __SHAPE_BITMAP_WATCHER_HPP__

#include <wx/wxsf/BitmapShape.h>
#include <wx/wxsf/DiagramManager.h>

#include <gaze.hpp>

#include "shapes/shape.pinner.hpp"

namespace Shape {

class BitmapWatcher : public wxSFBitmapShape, public gaze::watcher, public Shape::Pinner {
public:
    BitmapWatcher();
    BitmapWatcher(const BitmapWatcher& other);
    BitmapWatcher(
        const wxRealPoint& pos,
        gaze::source<wxBitmapBundle>* bmpBndl,
        wxSFDiagramManager* manager
    );

public:  // Pinner implementation
    inline virtual void MoveTo(const wxRealPoint& point) override {
        wxSFBitmapShape::MoveTo(point.x, point.y);
    }
    inline virtual wxRealPoint GetPosition() override {
        return wxSFBitmapShape::GetAbsolutePosition();
    }
    inline virtual wxRealPoint GetSize() override { return this->GetRectSize(); }

protected:  // Watcher implementation
    void subject_updated(const gaze::subject* subj) override;

private:
    void UpdateSize();

private:
    gaze::source<wxBitmapBundle>* bmpBndl{nullptr};
};

}  // namespace Shape

#endif  // __SHAPE_BITMAP_WATCHER_HPP__
