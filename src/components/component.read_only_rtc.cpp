#include "components/component.read_only_rtc.hpp"

#include "managers/manager.asset.hpp"

namespace Component {

void ReadOnlyRTC::Create(wxWindow *parent, const wxString &value) {
    wxRichTextCtrl::Create(parent, -1, value, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

    this->shadowBmp = Manager::Asset::GetMaterial(
        Model::Asset::Material::TEXT_BOTTOM_SHADOW,
        wxSize(-1, Constants::ShadowHeight())
    );

    this->SetEditable(false);

    this->SetCursor(wxCURSOR_DEFAULT);
    this->SetTextCursor(wxCURSOR_DEFAULT);

    this->SetBasicStyle(Constants::Attributes());
    this->SetBackgroundColour(Style::Color::Black());
    this->SetFontScale(Constants::FontScale());

    this->BindEvents();
}

void ReadOnlyRTC::BindEvents() {
    Bind(wxEVT_SET_FOCUS, [](wxFocusEvent &) {});
    Bind(wxEVT_LEFT_DOWN, [](wxMouseEvent &) {});
    Bind(wxEVT_RIGHT_UP, [](wxMouseEvent &) {});
    Bind(wxEVT_CHAR, [](wxKeyEvent &) {});
    Bind(wxEVT_KEY_DOWN, [](wxKeyEvent &) {});
}

void ReadOnlyRTC::PaintAboveContent(wxDC &dc) {
    const wxSize windowSize = this->GetClientSize();
    const wxBitmap bitmapToDraw =
        this->shadowBmp.GetBitmap(wxSize(windowSize.x, Constants::ShadowHeight()));

    int yOffset;
    this->CalcUnscrolledPosition(0, 0, nullptr, &yOffset);

    dc.DrawBitmap(bitmapToDraw, wxPoint(0, windowSize.y - Constants::ShadowHeight()), true);
}

}  // namespace Component
