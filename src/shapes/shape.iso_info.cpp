#include "shapes/shape.iso_info.hpp"

#include <wx/debug.h>
#include <wx/msgdlg.h>
#include <wx/wxsf/FlexGridShape.h>

#include "managers/manager.asset.hpp"
#include "models/model.asset.hpp"
#include "shapes/shape.bitmap_watcher.hpp"
#include "shapes/shape.ids.hpp"
#include "shapes/shape.text_watcher.hpp"
#include "style/style.color.hpp"
#include "style/style.spacing.hpp"
#include "wx/wxsf/ShapeBase.h"

namespace Shape {

XS_IMPLEMENT_CLONABLE_CLASS(Shape::ISOInfo, wxSFFlexGridShape);

ISOInfo::ISOInfo(const ISOInfo& other)
    : Shape::ISOInfo(
          other.isoFile,
          other.state,
          other.GetRelativePosition(),
          other.GetRectSize(),
          (wxSFDiagramManager*)(other.m_pParentManager)
      ) {}

ISOInfo::ISOInfo(
    gaze::source<wxString>* isoFile,
    gaze::source<State>* state,
    const wxRealPoint& pos,
    const wxRealPoint& size,
    wxSFDiagramManager* manager
)
    : wxSFFlexGridShape(pos, size, Constants::RowCount(), Constants::ColumnCount(), 8, manager) {
    wxLogDebug("Shape/ISOInfo: Initializing");
    this->RemoveStyle(sfsHIGHLIGHTING);
    this->RemoveStyle(sfsPOSITION_CHANGE);
    this->RemoveStyle(sfsSIZE_CHANGE);
    this->RemoveStyle(sfsSHOW_HANDLES);
    this->RemoveStyle(sfsHOVERING);
    this->SetHoverColour(Style::Color::Clear());
    this->SetFill(wxBrush(Style::Color::Clear()));
    this->SetBorder(wxPen(Style::Color::Clear()));

    this->isoFile = this->watch_assign(isoFile);
    this->state = this->watch_assign(state);

    this->UpdateStateValues(state->get());

    wxLogDebug("Shape/ISOInfo: Adding Icon shape");
    this->pIconShape = new Shape::BitmapWatcher(wxDefaultPosition, &this->iconBundle, manager);

    manager->AddShape(this->pIconShape, this, wxDefaultPosition, true, false);
    this->pIconShape->SetId(long(Shape::IDs::ISO_INFO_ICON));
    this->InsertToGrid(0, 0, this->pIconShape);

    wxLogDebug("Shape/ISOInfo: Adding TextGrid shape");
    wxSFFlexGridShape* pTextGrid = new wxSFFlexGridShape(
        wxRealPoint{wxDefaultPosition},
        wxRealPoint{wxDefaultPosition},
        Constants::TextGridRowCount(),
        Constants::TextGridColumnCount(),
        Style::Spacing::S4(),
        manager
    );
    manager->AddShape(pTextGrid, this, wxDefaultPosition, true, false);
    pTextGrid->SetId(long(Shape::IDs::ISO_INFO_TEXT_GRID));
    pTextGrid->SetFill(wxBrush(Style::Color::Clear()));
    pTextGrid->SetBorder(wxPen(Style::Color::Clear()));
    pTextGrid->RemoveStyle(sfsEMIT_EVENTS);
    this->InsertToGrid(0, 1, pTextGrid);

    wxLogDebug("Shape/ISOInfo: Adding Label shape");
    this->pLabelShape = new TextWatcher(wxDefaultPosition, this->isoFile, manager);
    manager->AddShape(this->pLabelShape, pTextGrid, wxDefaultPosition, true, false);
    this->pLabelShape->SetId(long(Shape::IDs::ISO_INFO_TITLE));
    this->pLabelShape->SetTextColour(Style::Color::White());
    // this->pLabelShape->SetFont(); // TODO[Amadeus]: Set font when font is actually available
    pTextGrid->InsertToGrid(0, 0, this->pLabelShape);

    wxLogDebug("Shape/ISOInfo: Adding Subtitle shape");
    this->pSubtitleShape = new TextWatcher(wxDefaultPosition, &this->subtitle, manager);
    manager->AddShape(this->pSubtitleShape, pTextGrid, wxDefaultPosition, true, false);
    this->pSubtitleShape->SetId(long(Shape::IDs::ISO_INFO_SUBTITLE));
    this->pSubtitleShape->SetTextColour(Style::Color::White());
    // this->pSubtitleShape->SetFont(); // TODO[Amadeus]: Set font when font is actually available
    pTextGrid->InsertToGrid(1, 0, this->pSubtitleShape);
}

void ISOInfo::subject_updated(const gaze::subject* subj) {
    if (subj == this->state) {
        this->UpdateStateValues(this->state->get());
    };
}

void ISOInfo::UpdateStateValues(State state) {
    this->UpdateIcon(state);
    this->UpdateSubtitle(state);
}

void ISOInfo::UpdateIcon(ISOInfo::State state) {
    wxBitmapBundle icon;
    switch (state) {
        case TO_SELECT_ISO:
            icon = Manager::Asset::GetIcon(Model::Asset::Icon::TWITTER, Constants::IconSize());
            break;
        case ISO_SELECTED:
            icon = Manager::Asset::GetIcon(Model::Asset::Icon::WEBSITE, Constants::IconSize());
            break;
    }
    this->iconBundle.set(icon);
}

void ISOInfo::UpdateSubtitle(ISOInfo::State state) {
    switch (state) {
        case TO_SELECT_ISO:
            this->subtitle.set("View Installation Guide");
            break;
        case ISO_SELECTED:
            this->subtitle.set("ISO File");
            break;
    }
}

}  // namespace Shape
