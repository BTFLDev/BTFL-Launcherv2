#include "elements/element.icon_button.hpp"

#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/msgdlg.h>

#include "managers/manager.asset.hpp"
#include "style/style.color.hpp"

wxDEFINE_EVENT(wxEVT_ICON_BUTTON, Element::IconButton::Event);

namespace Element {

IconButton::Event::Event(wxWindowID id, Model::Asset::Icon icon)
    : wxCommandEvent(wxEVT_ICON_BUTTON, id), icon(icon) {}

Model::Asset::Icon IconButton::Event::GetIcon() { return this->icon; }

void IconButton::Event::SetIcon(Model::Asset::Icon icon) { this->icon = icon; }

IconButton::IconButton(wxWindow* parent, Model::Asset::Icon icon)
    : wxWindow(parent, wxWindowID(icon), wxDefaultPosition, Constants::Size()),
      icon(icon),
      bitmap(Manager::Asset::GetIcon(icon, Constants::Size())) {
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->SetCursor(wxCURSOR_HAND);

    this->BindEvents();
}

void IconButton::BindEvents() {
    Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});

    Bind(wxEVT_PAINT, &IconButton::OnPaint, this);
    Bind(wxEVT_SIZE, &IconButton::OnSize, this);
    Bind(wxEVT_ENTER_WINDOW, &IconButton::OnEnterWindow, this);
    Bind(wxEVT_LEAVE_WINDOW, &IconButton::OnLeaveWindow, this);
    Bind(wxEVT_LEFT_DOWN, &IconButton::OnLeftDown, this);
}

void IconButton::OnSize(wxSizeEvent&) { this->SetSize(Constants::Size()); }

void IconButton::OnPaint(wxPaintEvent& event) {
    wxPaintDC pdc(this);
    wxGCDC dc(pdc);

    const wxSize currentSize = this->GetClientSize();
    const wxBitmap bmpToDraw = this->bitmap.GetBitmapFor(this);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(this->GetBackgroundColour()));
    dc.DrawBitmap(bmpToDraw, wxPoint(0, 0));

    if (this->bIsHovering) return;

    dc.SetBrush(wxBrush(Style::Color::Black(Constants::NonHoverOpacity())));
    dc.DrawRectangle(wxPoint(0, 0), currentSize);
}

void IconButton::OnLeaveWindow(wxMouseEvent& event) {
    this->bIsHovering = false;
    this->Refresh();
}

void IconButton::OnEnterWindow(wxMouseEvent& event) {
    this->bIsHovering = true;
    this->Refresh();
}

void IconButton::OnLeftDown(wxMouseEvent&) {
    Event event{this->GetId(), this->icon};
    event.SetEventObject(this);
    this->ProcessEvent(event);
}

}  // namespace Element
