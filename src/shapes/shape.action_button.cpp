#include "shapes/shape.action_button.hpp"

#include <wx/msgdlg.h>

#include "style/style.color.hpp"
#include "wx/wxsf/RoundRectShape.h"
#include "wx/wxxmlserializer/XmlSerializer.h"

namespace Shape {

XS_IMPLEMENT_CLONABLE_CLASS(Shape::ActionButton, wxSFRoundRectShape);

ActionButton::ActionButton(const ActionButton& other)
    : Shape::ActionButton(
          other.label,
          other.state,
          other.font,
          other.GetRelativePosition(),
          other.GetRectSize(),
          other.m_nRadius,
          (wxSFDiagramManager*)(other.m_pParentManager),
          other.icon != nullptr ? std::optional(other.icon) : std::nullopt,
          other.isEnabled != nullptr ? std::optional(other.isEnabled) : std::nullopt,
          other.xPadding != nullptr ? std::optional(other.xPadding) : std::nullopt,
          other.yPadding != nullptr ? std::optional(other.yPadding) : std::nullopt
      ) {}

ActionButton::ActionButton(
    gaze::source<wxString>* text,
    gaze::source<State>* state,
    const wxFont& font,
    const wxRealPoint& pos,
    const wxRealPoint& size,
    double radius,
    wxSFDiagramManager* manager,
    std::optional<gaze::source<wxBitmap>*> icon,
    std::optional<gaze::source<bool>*> isEnabled,
    std::optional<gaze::source<int>*> xPadding,
    std::optional<gaze::source<int>*> yPadding
)
    : wxSFRoundRectShape(pos, size, radius, manager) {
    this->AddStyle(sfsEMIT_EVENTS);

    this->RemoveStyle(sfsHIGHLIGHTING);
    this->RemoveStyle(sfsPOSITION_CHANGE);
    this->RemoveStyle(sfsSIZE_CHANGE);
    this->RemoveStyle(sfsSHOW_HANDLES);

    this->label = this->watch_assign(text);
    this->state = this->watch_assign(state);
    this->font = font;

    if (icon.has_value()) {
        this->icon = this->watch_assign(icon.value());
    }
    if (isEnabled.has_value()) {
        this->isEnabled = this->watch_assign(isEnabled.value());
    }
    if (xPadding.has_value()) {
        this->xPadding = this->watch_assign(xPadding.value());
    }
    if (yPadding.has_value()) {
        this->yPadding = this->watch_assign(yPadding.value());
    }

    this->UpdateStateValues();
    this->RecalculateSelf();
}

void ActionButton::subject_updated(const gaze::subject* subj) {
    if (subj == this->state) {
        this->UpdateStateValues();
    }
    this->RecalculateSelf();
}

void ActionButton::RecalculateSelf(const wxSize& soloIconSize) {
    wxSFShapeCanvas* pCanvas = this->GetParentCanvas();
    if (pCanvas == nullptr) {
        return;
    }

    wxSize labelSize = this->CalculateLabelSize(pCanvas);
    labelSize.y -= 5;  // ???
    this->xLabel = this->GetXPadding();

    this->SetRectSize(
        labelSize.x + (this->GetXPadding() * 2),
        labelSize.y + (this->GetYPadding() * 2)
    );

    if (this->icon != nullptr) {
        if (this->label->get().IsEmpty()) {
            if (soloIconSize != wxDefaultSize) {
                double curRatio = (double)soloIconSize.x / soloIconSize.y;
                if (curRatio > this->iconRatio) {
                    this->iconScale = (double)soloIconSize.y / this->icon->get().GetHeight();
                    this->xIcon = (soloIconSize.x / 2) -
                                  ((double)(this->icon->get().GetWidth() * this->iconScale) / 2) +
                                  this->GetXPadding();
                    this->yIcon = this->GetYPadding();
                } else {
                    this->iconScale = (double)soloIconSize.x / this->icon->get().GetWidth();
                    this->yIcon = (soloIconSize.y / 2) -
                                  (((double)this->icon->get().GetHeight() * this->iconScale) / 2) +
                                  this->GetYPadding();
                    this->xIcon = this->GetXPadding();
                }

                labelSize.x = (double)this->icon->get().GetWidth() * this->iconScale;
                labelSize.y = (double)this->icon->get().GetHeight() * this->iconScale;
            }
        } else {
            this->iconScale = double(labelSize.y - 4) / (this->icon->get().GetHeight());
            this->yIcon = this->GetYPadding() + 2;
            this->xIcon = this->GetXPadding();

            int bmpx = (double)this->icon->get().GetWidth() * this->iconScale;
            labelSize.x += bmpx + 10;
            this->xLabel += bmpx + 10;
        }
    }
}

wxSize ActionButton::CalculateLabelSize(wxSFShapeCanvas* pCanvas) {
    wxClientDC dc{pCanvas};
    dc.SetFont(this->font);
    return dc.GetMultiLineTextExtent(this->label->get());
}

void ActionButton::UpdateStateValues() {
    switch (this->state->get()) {
        case State::IDLE:
            this->SetFill(Constants::IdleFill());
            this->SetBorder(Constants::IdleBorder());
            this->labelColour = Style::Color::White();
            break;

        case State::PROCESSING:
            this->SetFill(Constants::ProcessingFill());
            this->SetBorder(Constants::ProcessingBorder());
            this->labelColour = Style::Color::White(Constants::ProcessingLabelColorAlpha());
            break;

        case State::SPECIAL:
            this->SetFill(Constants::SpacialFill());
            this->SetBorder(Constants::SpecialBorder());
            this->labelColour = Style::Color::Black();
            break;
    }
}

int ActionButton::GetXPadding() {
    if (this->xPadding == nullptr) {
        return Constants::DefaultXPadding();
    }

    return this->xPadding->get();
}

int ActionButton::GetYPadding() {
    if (this->yPadding == nullptr) {
        return Constants::DefaultYPadding();
    }

    return this->yPadding->get();
}

void ActionButton::DrawContent(wxDC& dc, bool isHovering) {
    dc.SetFont(this->font);
    dc.SetTextForeground(this->labelColour);
    wxRealPoint absolutePos = this->GetAbsolutePosition();

    dc.DrawText(
        this->label->get(),
        absolutePos + wxRealPoint{double(this->xLabel), double(this->GetYPadding())}
    );

    if (this->icon != nullptr) {
        dc.SetUserScale(this->iconScale, this->iconScale);
        wxRealPoint iconPos = (absolutePos + wxRealPoint{double(this->xIcon), double(this->yIcon)});
        iconPos.x /= this->iconScale;
        iconPos.y /= this->iconScale;

        if (isHovering) {
            dc.DrawBitmap(
                this->icon->get().ConvertToDisabled(Constants::DisabledIconBrightness()),
                iconPos,
                true
            );
        } else {
            dc.DrawBitmap(this->icon->get(), iconPos, true);
        }

        dc.SetUserScale(Constants::DefaultUserScale(), Constants::DefaultUserScale());
    }
}

void ActionButton::DrawNormal(wxDC& dc) {
    wxSFRoundRectShape::DrawNormal(dc);
    this->DrawContent(dc, false);
}

void ActionButton::DrawHover(wxDC& dc) {
    wxBrush fillCache = this->GetFill();
    wxColour labelColourCache = this->labelColour;

    SetFill(wxBrush(Style::Color::TextSuperLightGrey()));
    this->labelColour = Style::Color::Black();

    wxSFRoundRectShape::DrawHover(dc);
    this->DrawContent(dc, true);

    this->SetFill(fillCache);
    this->labelColour = labelColourCache;
}

void ActionButton::OnMouseEnter(const wxPoint& pos) {
    this->GetParentCanvas()->SetCursor(wxCURSOR_HAND);
}

void ActionButton::OnMouseLeave(const wxPoint& pos) {
    this->GetParentCanvas()->SetCursor(wxCURSOR_DEFAULT);
}

}  // namespace Shape
