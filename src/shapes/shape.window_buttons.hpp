#ifndef __SHAPE_WINDOW_BUTTONS_HPP__
#define __SHAPE_WINDOW_BUTTONS_HPP__

#include <wx/bmpbndl.h>
#include <wx/gdicmn.h>
#include <wx/wxsf/BitmapShape.h>
#include <wx/wxsf/FlexGridShape.h>
#include <wx/wxsf/ShapeCanvas.h>
#include <wx/wxxmlserializer/XmlSerializer.h>

#include <gaze.hpp>

#include "managers/manager.asset.hpp"
#include "models/model.asset.hpp"
#include "shapes/shape.pinner.hpp"

namespace Shape {

class WindowButtons : public wxSFFlexGridShape, public gaze::watcher, public Shape::Pinner {
public:
    WindowButtons() {}
    WindowButtons(const WindowButtons& other);
    WindowButtons(const wxRealPoint& pos, const wxRealPoint& size, wxSFDiagramManager* manager);

public:  // Pinner implementation
    inline virtual void MoveTo(const wxRealPoint& point) override {
        wxSFFlexGridShape::MoveTo(point.x, point.y);
    }
    inline virtual wxRealPoint GetPosition() override {
        return wxSFFlexGridShape::GetAbsolutePosition();
    }
    inline virtual wxRealPoint GetSize() override { return this->GetRectSize(); }

protected:  // Watcher implementation
    virtual void subject_updated(const gaze::subject* subj) override;

private:
    gaze::source<wxBitmapBundle> infoIcon = {
        Manager::Asset::GetIcon(Model::Asset::Icon::REDDIT, Constants::IconSize())
    };

private:
    struct Constants {
        constexpr inline static const int RowCount() { return 1; }
        constexpr inline static const int ColumnCount() { return 3; }

        inline static const wxSize IconSize() { return {24, 24}; }
    };

    XS_DECLARE_CLONABLE_CLASS(WindowButtons);
};

}  // namespace Shape

#endif  // __SHAPE_WINDOW_BUTTONS_HPP__
