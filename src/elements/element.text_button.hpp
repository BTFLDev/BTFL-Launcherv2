#ifndef __TEXT_BUTTON_HPP__
#define __TEXT_BUTTON_HPP__

#include <wx/stattext.h>
#include <wx/window.h>

namespace Element {

class TextButton : public wxStaticText {
public:
    TextButton() {}
    TextButton(
        wxWindow* parent,
        wxWindowID id,
        const wxString& text,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0
    ) {
        this->Create(parent, id, text, pos, size, style);
    }

    void Create(
        wxWindow* parent,
        wxWindowID id,
        const wxString& text,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0
    );

    virtual bool SetForegroundColour(const wxColour& colour) override;

private:
    void BindEvents();

    void OnLeftDown(wxMouseEvent& event);
    void OnEnterWindow(wxMouseEvent& event);
    void OnLeaveWindow(wxMouseEvent& event);

private:
    wxColour textColour;

private:
    struct Constants {
        constexpr inline static int MixColourPercent() { return 20; }
    };
};

}  // namespace Element

#endif  // __TEXT_BUTTON_HPP__
