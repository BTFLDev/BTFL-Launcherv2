#include "shapes/shape.window_buttons.hpp"

#include <wx/gdicmn.h>

#include "shapes/shape.bitmap_watcher.hpp"
#include "shapes/shape.ids.hpp"
#include "style/style.color.hpp"

namespace Shape {

WindowButtons::WindowButtons(const WindowButtons& other)
    : Shape::WindowButtons(
          other.GetRelativePosition(),
          other.GetRectSize(),
          (wxSFDiagramManager*)(other.m_pParentManager)
      ) {}

WindowButtons::WindowButtons(
    const wxRealPoint& pos,
    const wxRealPoint& size,
    wxSFDiagramManager* manager
)
    : wxSFFlexGridShape(pos, size, Constants::RowCount(), Constants::ColumnCount(), 8, manager) {
    wxLogDebug("Shape/WindowButtons: Initializing");

    wxLogDebug("Shape/WindowButtons: Adding TextGrid shape");
    Shape::BitmapWatcher* pInfoButton = new Shape::BitmapWatcher(
        wxRealPoint{wxDefaultPosition},
        &this->infoIcon,
        manager
    );
    manager->AddShape(pInfoButton, this, wxDefaultPosition, true, false);
    pInfoButton->SetId(long(Shape::IDs::ISO_INFO_TEXT_GRID));
    pInfoButton->SetFill(wxBrush(Style::Color::Clear()));
    this->InsertToGrid(0, 0, pInfoButton);
}

}  // namespace Shape
