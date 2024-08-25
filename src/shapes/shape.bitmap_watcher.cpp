#include "shapes/shape.bitmap_watcher.hpp"

#include <wx/msgdlg.h>
#include <wx/wxsf/DiagramManager.h>
#include <wx/wxsf/TextShape.h>

#include "wx/wxsf/BitmapShape.h"

namespace Shape {

BitmapWatcher::BitmapWatcher() : wxSFBitmapShape() {}

BitmapWatcher::BitmapWatcher(const BitmapWatcher& other)
    : BitmapWatcher(
          other.m_nRelativePosition,
          other.bmpBndl,
          (wxSFDiagramManager*)other.m_pParentManager
      ) {}

BitmapWatcher::BitmapWatcher(
    const wxRealPoint& pos,
    gaze::source<wxBitmapBundle>* bmpBndl,
    wxSFDiagramManager* manager
)
    : wxSFBitmapShape(
          pos,
          bmpBndl->get().GetBitmapFor((wxWindow*)manager->GetShapeCanvas()),
          manager
      ) {
    this->RemoveStyle(sfsHIGHLIGHTING);
    this->RemoveStyle(sfsPOSITION_CHANGE);
    this->RemoveStyle(sfsSIZE_CHANGE);
    this->RemoveStyle(sfsSHOW_HANDLES);
    this->RemoveStyle(sfsHOVERING);

    this->bmpBndl = this->watch_assign(bmpBndl);
    this->UpdateSize();
}

void BitmapWatcher::subject_updated(const gaze::subject* subj) {
    if (subj == this->bmpBndl) {
        wxBitmap bmp = this->bmpBndl->get().GetBitmapFor((wxWindow*)this->GetParentCanvas());
        this->CreateFromBitmap(bmp);
        this->UpdateSize();
    }
}

void BitmapWatcher::UpdateSize() {
    const wxSize bmpSize = this->m_Bitmap.GetLogicalSize();
    this->SetRectSize(bmpSize.x, bmpSize.y);
}

}  // namespace Shape
