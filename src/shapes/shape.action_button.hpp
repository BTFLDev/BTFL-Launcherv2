#ifndef __SHAPE_ACTION_BUTTON_HPP__
#define __SHAPE_ACTION_BUTTON_HPP__

#include <wx/gdicmn.h>
#include <wx/wxsf/RoundRectShape.h>

#include <optional>

#include "gaze.hpp"
#include "shapes/shape.pinner.hpp"
#include "style/style.color.hpp"
#include "wx/wxsf/ShapeCanvas.h"
#include "wx/wxxmlserializer/XmlSerializer.h"

namespace Shape {

class ActionButton : public wxSFRoundRectShape, public gaze::watcher, public Shape::Pinner {
public:
    enum class State {
        IDLE,
        PROCESSING,
        SPECIAL,
    };

public:
    ActionButton() {}
    ActionButton(const ActionButton& other);
    ActionButton(
        gaze::source<wxString>* text,
        gaze::source<State>* state,
        const wxFont& font,
        const wxRealPoint& pos,
        const wxRealPoint& size,
        double radius,
        wxSFDiagramManager* manager,
        std::optional<gaze::source<wxBitmap>*> icon = std::nullopt,
        std::optional<gaze::source<bool>*> isEnabled = std::nullopt,
        std::optional<gaze::source<int>*> xPadding = std::nullopt,
        std::optional<gaze::source<int>*> yPadding = std::nullopt
    );

public:  // Pinner implementation
    inline virtual void MoveTo(const wxRealPoint& point) override {
        wxSFRoundRectShape::MoveTo(point.x, point.y);
    }
    inline virtual wxRealPoint GetPosition() override {
        return wxSFRoundRectShape::GetAbsolutePosition();
    }
    inline virtual wxRealPoint GetSize() override { return this->GetRectSize(); }

protected:
    virtual void subject_updated(const gaze::subject* subj) override;

private:
    void RecalculateSelf(const wxSize& soloIconSize = wxDefaultSize);
    wxSize CalculateLabelSize(wxSFShapeCanvas* pCanvas);

    void UpdateStateValues();

    int GetXPadding();
    int GetYPadding();

    void DrawContent(wxDC& dc, bool isHovering);

    virtual void DrawNormal(wxDC& dc) override;
    virtual void DrawHover(wxDC& dc) override;

    virtual void OnMouseEnter(const wxPoint& pos) override;
    virtual void OnMouseLeave(const wxPoint& pos) override;

private:
    gaze::source<wxString>* label{nullptr};
    gaze::source<State>* state{nullptr};

    gaze::source<bool>* isEnabled{nullptr};
    gaze::source<int>* xPadding{nullptr};
    gaze::source<int>* yPadding{nullptr};

    wxFont font{};
    wxColour labelColour{Style::Color::White()};

    int xLabel = Constants::DefaultXLabel();

    gaze::source<wxBitmap>* icon{nullptr};
    double iconScale = 1.0, iconRatio = 1.0;
    int xIcon = Constants::DefaultXBitmap(), yIcon = Constants::DefaultYBitmap();

private:
    struct Constants {
        constexpr inline static const double DefaultUserScale() { return 1.0; }

        constexpr inline static const int DefaultXPadding() { return 35; }
        constexpr inline static const int DefaultYPadding() { return 12; }

        constexpr inline static const int DefaultXLabel() { return 30; }

        constexpr inline static const int DefaultXBitmap() { return 30; }
        constexpr inline static const int DefaultYBitmap() { return 0; }

        constexpr inline static const int DisabledIconBrightness() { return 0; }

        inline static const wxBrush IdleFill() { return wxBrush(Style::Color::White(50)); }
        inline static const wxBrush ProcessingFill() { return *wxTRANSPARENT_BRUSH; }
        inline static const wxBrush SpacialFill() { return wxBrush(Style::Color::White()); }
        inline static const wxPen IdleBorder() { return *wxTRANSPARENT_PEN; }
        inline static const wxPen ProcessingBorder() { return wxPen(Style::Color::White(50), 2); }
        inline static const wxPen SpecialBorder() { return *wxTRANSPARENT_PEN; }

        constexpr inline static const unsigned char ProcessingLabelColorAlpha() { return 50; }
    };

    XS_DECLARE_CLONABLE_CLASS(ActionButton);
};

}  // namespace Shape

#endif  // __SHAPE_ACTION_BUTTON_HPP__
