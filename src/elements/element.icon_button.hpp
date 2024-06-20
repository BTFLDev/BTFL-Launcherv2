#ifndef _ELEMENT_ICONBUTTON_HPP_
#define _ELEMENT_ICONBUTTON_HPP_

#include <wx/bmpbndl.h>
#include <wx/window.h>

#include "models/model.asset.hpp"

namespace Element {

class IconButton : public wxWindow {
public:
    class Event : public wxCommandEvent {
    public:
        Event() {}
        Event(wxWindowID id, Model::Asset::Icon icon);

        void SetIcon(Model::Asset::Icon icon);
        Model::Asset::Icon GetIcon();

    private:
        Model::Asset::Icon icon;
    };

public:
    IconButton(wxWindow* parent, Model::Asset::Icon icon);

private:
    void BindEvents();

    // Event handlers

    void OnSize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);

    void OnLeftDown(wxMouseEvent& event);
    void OnEnterWindow(wxMouseEvent& event);
    void OnLeaveWindow(wxMouseEvent& event);

private:
    const Model::Asset::Icon icon;

    const wxBitmapBundle bitmap;
    bool bIsHovering = false;

private:
    struct Constants {
        inline static wxSize Size() { return {24, 24}; }
        inline static unsigned char NonHoverOpacity() { return 125; }
    };
};

}  // namespace Element

wxDECLARE_EVENT(EVT_ICON_BUTTON, Element::IconButton::Event);

#endif  // _ELEMENT_ICONBUTTON_HPP_
