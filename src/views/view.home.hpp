#ifndef __VIEW_HOME_HPP__
#define __VIEW_HOME_HPP__

#include <wx/event.h>
#include <wx/msgdlg.h>
#include <wx/wxsf/SFEvents.h>

#include <gaze.hpp>

#include "shapes/shape.action_button.hpp"
#include "shapes/shape.iso_info.hpp"
#include "shapes/shape.pinner.hpp"
#include "utils/background_image_canvas.hpp"
#include "view_models/view_model.home.hpp"

namespace View {

class Home : public Utils::BackgroundImageCanvas, public gaze::watcher, public Shape::Pinner {
public:
    Home() {}
    Home(wxWindow* parent, wxSFDiagramManager* manager, ViewModel::Home* viewModel);
    virtual ~Home();

    void Create(wxWindow* parent, wxSFDiagramManager* manager, ViewModel::Home* viewModel);

public:  // Shape::Pinner implementation
    inline virtual void MoveTo(const wxRealPoint&) override { /* no-op */ }
    inline virtual wxRealPoint GetPosition() override { return {0.0, 0.0}; }
    inline virtual wxRealPoint GetSize() override {
        const wxSize size = Utils::BackgroundImageCanvas::GetSize();
        return {static_cast<double>(size.x), static_cast<double>(size.y)};
    }

protected:
    virtual void subject_updated(const gaze::subject* subj) override;

private:
    void BindEvents();
    void PinButtons();

    void OnMainButtonClick(wxSFShapeMouseEvent& event);
    void OnSettingsButtonClick(wxSFShapeMouseEvent& event);

    void OnSize(wxSizeEvent& size);

private:
    ViewModel::Home* pViewModel{nullptr};

    Shape::ActionButton* pMainButton{nullptr};
    Shape::ActionButton* pSettingsButton{nullptr};
    Shape::ISOInfo* pIsoInfoShape{nullptr};

private:
    struct Constants {
        constexpr inline static const double MainButtonCornerRadius() { return 3.0; }
        inline static const wxRealPoint MainButtonOffset() { return {50.0, -50.0}; }
        inline static const wxRealPoint SettingsButtonOffset() { return {8.0, 0.0}; }
        inline static const wxRealPoint ISOInfoOffset() { return {0.0, -8.0}; }
    };
};

}  // namespace View

#endif  // __VIEW_HOME_HPP__
