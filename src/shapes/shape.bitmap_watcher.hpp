#ifndef __SHAPE_BITMAP_WATCHER_HPP__
#define __SHAPE_BITMAP_WATCHER_HPP__

#include <gaze.hpp>

#include "wx/wxsf/BitmapShape.h"
#include "wx/wxsf/DiagramManager.h"

namespace Shape {

class BitmapWatcher : public wxSFBitmapShape, public gaze::watcher {
public:
    BitmapWatcher();
    BitmapWatcher(const BitmapWatcher& other);
    BitmapWatcher(
        const wxRealPoint& pos,
        gaze::source<wxBitmapBundle>* bmpBndl,
        wxSFDiagramManager* manager
    );

protected: // Watcher implementation
    void subject_updated(const gaze::subject* subj) override;

private:
    void UpdateSize();

private:
    gaze::source<wxBitmapBundle>* bmpBndl{nullptr};
};

}  // namespace Shape

#endif  // __SHAPE_BITMAP_WATCHER_HPP__
