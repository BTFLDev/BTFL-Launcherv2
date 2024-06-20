#include "components/component.divider.hpp"

#include <wx/dcclient.h>

#include "style/style.color.hpp"
#include "style/style.spacing.hpp"

namespace Component {

Divider::Divider(wxWindow *parent)
    : wxWindow(parent, -1, wxDefaultPosition, wxSize(-1, Style::Spacing::S1())) {
    this->BindEvents();
}

void Divider::BindEvents() { Bind(wxEVT_PAINT, &Divider::OnPaint, this); }

void Divider::OnPaint(wxPaintEvent &evt) {
    wxPaintDC dc(this);

    const wxSize currentSize = this->GetClientSize();
    const wxSize halfSize(currentSize.x / 2, Style::Spacing::S1());

    const int yPoint = currentSize.y / 2;
    const wxPoint leftPoint(0, yPoint);
    const wxPoint rightPoint(currentSize.x / 2, yPoint);

    dc.GradientFillLinear(
        wxRect(leftPoint, halfSize),
        Style::Color::Black(60),
        Style::Color::White(60)
    );
    dc.GradientFillLinear(
        wxRect(rightPoint, halfSize),
        Style::Color::White(60),
        Style::Color::Black(60)
    );
}

}  // namespace Component
