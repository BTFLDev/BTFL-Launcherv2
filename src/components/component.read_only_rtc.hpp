#ifndef _COMPONENT_READONLYRTC_HPP_
#define _COMPONENT_READONLYRTC_HPP_

#include <wx/bmpbndl.h>
#include <wx/richtext/richtextctrl.h>

#include "style/style.color.hpp"
#include "style/style.spacing.hpp"

namespace Component {

class ReadOnlyRTC : public wxRichTextCtrl {
public:
    ReadOnlyRTC() {}
    ReadOnlyRTC(wxWindow *parent, const wxString &value = wxEmptyString) {
        this->Create(parent, value);
    }

    void Create(wxWindow *parent, const wxString &value = wxEmptyString);

    virtual void PaintAboveContent(wxDC &dc) override;
    inline virtual void Paste() override{};

private:
    void BindEvents();

private:
    wxBitmapBundle shadowBmp;

private:
    struct Constants {
        inline static const double FontScale() { return 1.13; }
        inline static const int ShadowHeight() { return Style::Spacing::S40(); }
        inline static const wxRichTextAttr Attributes() {
            wxRichTextAttr attr;
            attr.SetFont(wxFontInfo(11).FaceName("Lora"));
            attr.SetAlignment(wxTEXT_ALIGNMENT_JUSTIFIED);
            attr.SetLeftIndent(Style::Spacing::S64());
            attr.SetRightIndent(Style::Spacing::S64());
            attr.SetLineSpacing(Style::Spacing::S8());
            attr.SetTextColour(Style::Color::White());
            return attr;
        }
    };
};

}  // namespace Component

#endif  // _COMPONENT_READONLYRTC_HPP_
