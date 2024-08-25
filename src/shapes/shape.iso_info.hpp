#ifndef __SHAPE_ISO_INFO_HPP__
#define __SHAPE_ISO_INFO_HPP__

#include <wx/gdicmn.h>
#include <wx/wxsf/BitmapShape.h>
#include <wx/wxsf/FlexGridShape.h>
#include <wx/wxsf/ShapeCanvas.h>
#include <wx/wxxmlserializer/XmlSerializer.h>

#include <gaze.hpp>

#include "shapes/shape.bitmap_watcher.hpp"
#include "shapes/shape.pinner.hpp"
#include "shapes/shape.text_watcher.hpp"
#include "style/style.color.hpp"

namespace Shape {

class ISOInfo : public wxSFFlexGridShape, public gaze::watcher, public Shape::Pinner {
public:
    enum State {
        TO_SELECT_ISO,
        ISO_SELECTED,
    };

public:
    ISOInfo() {}
    ISOInfo(const ISOInfo& other);
    ISOInfo(
        gaze::source<wxString>* isoFile,
        gaze::source<State>* state,
        const wxRealPoint& pos,
        const wxRealPoint& size,
        wxSFDiagramManager* manager
    );

public:  // Pinner implementation
    inline virtual void MoveTo(const wxRealPoint& point) override {
        wxSFFlexGridShape::MoveTo(point.x, point.y);
    }
    inline virtual wxRealPoint GetPosition() override {
        return wxSFFlexGridShape::GetAbsolutePosition();
    }
    inline virtual wxRealPoint GetSize() override { return this->GetRectSize(); }

protected:
    virtual void subject_updated(const gaze::subject* subj) override;

private:
    //     void RecalculateSelf();
    void UpdateStateValues(State state);

    void UpdateIcon(State state);
    void UpdateSubtitle(ISOInfo::State state);

    //     virtual void DrawNormal(wxDC& dc) override;
    //     virtual void DrawHover(wxDC& dc) override;
    //
    //     virtual void OnMouseEnter(const wxPoint& pos) override;
    //     virtual void OnMouseLeave(const wxPoint& pos) override;

private:
    gaze::source<wxString>* isoFile{nullptr};
    gaze::source<wxString> subtitle{"", this};
    gaze::source<State>* state{nullptr};

    wxFont font{};
    wxColour labelColour{Style::Color::White()};

    gaze::source<wxBitmapBundle> iconBundle{wxBitmapBundle(), this};

    Shape::BitmapWatcher* pIconShape{nullptr};
    Shape::TextWatcher* pLabelShape{nullptr};
    Shape::TextWatcher* pSubtitleShape{nullptr};

private:
    struct Constants {
        constexpr inline static const int RowCount() { return 1; }
        constexpr inline static const int ColumnCount() { return 2; }

        constexpr inline static const int TextGridRowCount() { return 2; }
        constexpr inline static const int TextGridColumnCount() { return 1; }

        inline static const wxSize IconSize() { return {32, 32}; }

        inline static const wxBrush IdleFill() { return wxBrush(Style::Color::White(50)); }
        inline static const wxBrush ProcessingFill() { return *wxTRANSPARENT_BRUSH; }
        inline static const wxBrush SpacialFill() { return wxBrush(Style::Color::White()); }
        inline static const wxPen IdleBorder() { return *wxTRANSPARENT_PEN; }
        inline static const wxPen ProcessingBorder() { return wxPen(Style::Color::White(50), 2); }
        inline static const wxPen SpecialBorder() { return *wxTRANSPARENT_PEN; }

        constexpr inline static const unsigned char ProcessingLabelColorAlpha() { return 50; }
    };

    XS_DECLARE_CLONABLE_CLASS(ISOInfo);
};

}  // namespace Shape

#endif  // __SHAPE_ISO_INFO_HPP__
