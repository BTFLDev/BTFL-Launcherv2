#include "shapes/shape.text_watcher.hpp"

#include <wx/msgdlg.h>
#include <wx/wxsf/DiagramManager.h>
#include <wx/wxsf/TextShape.h>
#include "wx/wxsf/ShapeBase.h"

namespace Shape {

TextWatcher::TextWatcher() : wxSFTextShape() {}

TextWatcher::TextWatcher(const TextWatcher& other)
    : TextWatcher(
          other.m_nRelativePosition,
          other.text,
          (wxSFDiagramManager*)other.m_pParentManager
      ) {}

TextWatcher::TextWatcher(
    const wxRealPoint& pos,
    gaze::source<wxString>* text,
    wxSFDiagramManager* manager
)
    : wxSFTextShape(pos, text->get(), manager) {
    wxLogDebug("Shape/TextWatcher: Initializing with text \"%s\"", text->get());
    this->RemoveStyle(sfsHIGHLIGHTING);
    this->RemoveStyle(sfsPOSITION_CHANGE);
    this->RemoveStyle(sfsSIZE_CHANGE);
    this->RemoveStyle(sfsSHOW_HANDLES);
    this->RemoveStyle(sfsHOVERING);

    this->text = this->watch_assign(text);
}

void TextWatcher::subject_updated(const gaze::subject* subj) {
    if (subj == this->text) {
        this->SetText(this->text->get());
    }
}

}  // namespace Shape
