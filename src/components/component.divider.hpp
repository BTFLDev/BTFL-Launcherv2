#ifndef _COMPONENT_DIVIDER_HPP_
#define _COMPONENT_DIVIDER_HPP_

#include <wx/window.h>

namespace Component {

class Divider : public wxWindow {
public:
    Divider(wxWindow* parent);

private:
    void BindEvents();
    void OnPaint(wxPaintEvent& evt);
};

}  // namespace Component

#endif  // _COMPONENT_DIVIDER_HPP_
