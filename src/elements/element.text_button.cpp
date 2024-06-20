#include "elements/element.text_button.hpp"

#include "style/style.color.hpp"
#include "utils/colour.hpp"

namespace Element {

void TextButton::Create(
    wxWindow* parent,
    wxWindowID id,
    const wxString& text,
    const wxPoint& pos,
    const wxSize& size,
    long style
) {
    wxStaticText::Create(parent, id, text, pos, size, style);

    this->textColour = this->GetForegroundColour();

    this->SetCursor(wxCURSOR_HAND);
    this->BindEvents();
}

bool TextButton::SetForegroundColour(const wxColour& colour) {
    this->textColour = colour;
    return wxStaticText::SetForegroundColour(colour);
}

void TextButton::BindEvents() {
    Bind(wxEVT_LEFT_DOWN, &TextButton::OnLeftDown, this);
    Bind(wxEVT_ENTER_WINDOW, &TextButton::OnEnterWindow, this);
    Bind(wxEVT_LEAVE_WINDOW, &TextButton::OnLeaveWindow, this);
}

void TextButton::OnLeftDown(wxMouseEvent& event) {
    wxCommandEvent evt{wxEVT_BUTTON, this->GetId()};
    evt.SetString(this->GetLabel());
    evt.SetEventObject(this);
    this->ProcessCommand(evt);
}

void TextButton::OnEnterWindow(wxMouseEvent& event) {
    wxStaticText::SetForegroundColour(
        Utils::MixColours(this->textColour, Style::Color::Black(), Constants::MixColourPercent())
    );
    this->Update();
    this->Refresh();
}

void TextButton::OnLeaveWindow(wxMouseEvent& event) {
    wxStaticText::SetForegroundColour(this->textColour);
    this->Update();
    this->Refresh();
}

}  // namespace Element
