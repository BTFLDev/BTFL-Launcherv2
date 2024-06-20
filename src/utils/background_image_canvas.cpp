#include "utils/background_image_canvas.hpp"

#include <wx/event.h>
#include <wx/log.h>
#include <wx/msgdlg.h>

#include <cstdlib>

namespace Utils {

void BackgroundImageCanvas::Create(
    wxWindow* parent,
    wxSFDiagramManager* manager,
    std::vector<wxBitmap> backgrounds,
    bool rotate,
    bool move
) {
    if (manager == nullptr) {
        manager = new wxSFDiagramManager;
    }

    wxSFShapeCanvas::Create(parent);

    this->vBackgrounds = backgrounds;
    this->bBgMoveEnabled = move;
    this->bgAnimTimer.SetOwner(this, TimerIDs::BG_ANIM);
    this->bgChangeTimer.SetOwner(this, TimerIDs::BG_CHANGE);
    this->bgTriggerChangeTimer.SetOwner(this, TimerIDs::BG_TRIGGER_CHANGE);

    this->SetDiagramManager(manager);
    this->EnableGC(true);

    this->BindEvents();

    this->EnableRotation(rotate);
}

void BackgroundImageCanvas::BindEvents() {
    Bind(wxEVT_SIZE, &BackgroundImageCanvas::_OnSize, this);
    Bind(wxEVT_ENTER_WINDOW, &BackgroundImageCanvas::OnEnterWindow, this);
    Bind(wxEVT_LEAVE_WINDOW, &BackgroundImageCanvas::OnLeaveWindow, this);

    Bind(wxEVT_TIMER, &BackgroundImageCanvas::OnBackgroundAnimTimer, this, TimerIDs::BG_ANIM);
    Bind(wxEVT_TIMER, &BackgroundImageCanvas::OnBackgroundChangeTimer, this, TimerIDs::BG_CHANGE);
    Bind(
        wxEVT_TIMER,
        &BackgroundImageCanvas::OnBackgroundTriggerChangeTimer,
        this,
        TimerIDs::BG_TRIGGER_CHANGE
    );
}

void BackgroundImageCanvas::EnableRotation(bool rotate) {
    if (this->vBackgrounds.size() <= 1) {
        rotate = false;
    }

    if (rotate) {
        this->bgTriggerChangeTimer.StartOnce(Constants::BgTriggerChangeIntervalMs());
    } else {
        this->bgTriggerChangeTimer.Stop();
    }
}

void BackgroundImageCanvas::DoAnimateBackground() {
    this->UpdateOverlayColor();
    this->UpdateBackgroundPosition();

    if (!this->bShouldResetBgPosition &&
        this->overlayColour.Alpha() == Constants::MinOverlayAlpha()) {
        this->bgAnimTimer.Stop();
    }
}

void BackgroundImageCanvas::UpdateOverlayColor() {
    unsigned char currentOverlayAlpha = this->overlayColour.Alpha();
    if (this->bShouldDarkenOverlay) {
        currentOverlayAlpha += Constants::OverlayAlphaChange();
        if (currentOverlayAlpha >= Constants::MaxAllowedOverlayAlpha()) {
            currentOverlayAlpha = Constants::MaxOverlayAlpha();
            this->bShouldDarkenOverlay = false;
            this->bgChangeTimer.StartOnce(Constants::BgChangeIntervalMs());
        }
    } else if (this->bShouldLightenOverlay) {
        currentOverlayAlpha -= Constants::OverlayAlphaChange();
        if (currentOverlayAlpha <= Constants::MinAllowedOverlayAlpha()) {
            currentOverlayAlpha = Constants::MinOverlayAlpha();
            this->bShouldLightenOverlay = false;
            this->bgTriggerChangeTimer.StartOnce(Constants::BgTriggerChangeIntervalMs());
        }
    }

    this->overlayColour = Style::Color::Black(currentOverlayAlpha);
}

void BackgroundImageCanvas::UpdateBackgroundPosition() {
    if (this->bShouldResetBgPosition) {
        this->nBackgroundXOffset -=
            Constants::BgPositionResetChange() *
            ((this->nBackgroundXOffset > 0) - (this->nBackgroundXOffset < 0));
        this->nBackgroundYOffset -=
            Constants::BgPositionResetChange() *
            ((this->nBackgroundYOffset > 0) - (this->nBackgroundYOffset < 0));

        this->bShouldResetBgPosition =
            std::abs(this->nBackgroundXOffset) >= 2 || std::abs(this->nBackgroundYOffset) >= 2;
    }
}

void BackgroundImageCanvas::OnSize(wxSizeEvent& event) {
    const wxBitmap& background = this->CurrentBackground();

    const wxSize size = this->GetSize();
    const float fCurRatio = (float)size.x / size.y;
    const float fBgRatio = (float)background.GetWidth() / background.GetHeight();
    const int nOverallOffset = Constants::MaxBackgroundOffset() * 2;

    if (fCurRatio > fBgRatio) {
        this->fBgScale = (float)(size.x + nOverallOffset) / background.GetWidth();
        this->nBackgroundY =
            ((size.y - (background.GetHeight() * this->fBgScale)) / 2) / this->fBgScale;
        this->nBackgroundX = -Constants::MaxBackgroundOffset() / this->fBgScale;
    } else {
        this->fBgScale = (float)(size.y + nOverallOffset) / background.GetHeight();
        this->nBackgroundX =
            ((size.x - (background.GetWidth() * this->fBgScale)) / 2) / this->fBgScale;
        this->nBackgroundY = -Constants::MaxBackgroundOffset() / this->fBgScale;
    }

    this->InvalidateVisibleRect();
}

void BackgroundImageCanvas::OnEnterWindow(wxMouseEvent& event) {
    this->bShouldResetBgPosition = false;
    this->mouseEnterPosition = event.GetPosition();
}

void BackgroundImageCanvas::OnLeaveWindow(wxMouseEvent& event) {
    // Do this so that the canvas unhovers any shape that it
    // thinks is still under the mouse
    wxPoint eventPos = event.GetPosition();
    event.SetPosition(wxPoint{0, 0});
    wxSFShapeCanvas::OnMouseMove(event);
    event.SetPosition(eventPos);

    this->bShouldResetBgPosition = true;
    this->bgAnimTimer.Start(Constants::BgAnimIntervalMs());
}

void BackgroundImageCanvas::OnBackgroundAnimTimer(wxTimerEvent& event) {
    this->DoAnimateBackground();
    this->Refresh();
    this->Update();
}

void BackgroundImageCanvas::OnBackgroundChangeTimer(wxTimerEvent& event) {
    const int oldBgIdx = this->nCurrentBgIdx;

    while (this->nCurrentBgIdx == oldBgIdx) {
        this->nCurrentBgIdx = std::rand() % this->vBackgrounds.size();
    }

    this->bShouldLightenOverlay = true;
    this->bgAnimTimer.Start(Constants::BgAnimIntervalMs());
}

void BackgroundImageCanvas::OnBackgroundTriggerChangeTimer(wxTimerEvent& event) {
    this->bShouldDarkenOverlay = true;
    this->bgAnimTimer.Start(Constants::BgAnimIntervalMs());
}

void BackgroundImageCanvas::OnMouseMove(wxMouseEvent& event) {
    wxSFShapeCanvas::OnMouseMove(event);

    if (!this->bBgMoveEnabled) {
        return;
    }

    wxSize clientSize = this->GetClientSize();
    wxPoint mousePos = event.GetPosition();

    this->nBackgroundXOffset =
        (double)((this->mouseEnterPosition.x - mousePos.x) * Constants::MaxBackgroundOffset()) /
        clientSize.x;
    this->nBackgroundYOffset =
        (double)((this->mouseEnterPosition.y - mousePos.y) * Constants::MaxBackgroundOffset()) /
        clientSize.y;

    this->InvalidateVisibleRect();
    this->DoAnimateBackground();
}

void BackgroundImageCanvas::OnUpdateVirtualSize(wxRect& rect) {
    rect.SetTopLeft(wxPoint{0, 0});
    rect.SetSize(this->GetClientSize());
}

void BackgroundImageCanvas::DrawBackground(wxDC& dc, bool fromPaint) {
    dc.SetUserScale(this->fBgScale, this->fBgScale);
    dc.DrawBitmap(
        this->CurrentBackground(),
        this->nBackgroundX + this->nBackgroundXOffset,
        this->nBackgroundY + this->nBackgroundYOffset
    );
    dc.SetUserScale(1.0, 1.0);

    if (this->overlayColour.Alpha() != Constants::MinOverlayAlpha()) {
        dc.SetBrush(wxBrush(this->overlayColour));
        dc.DrawRectangle(wxPoint{0, 0}, this->GetSize() + wxSize{1, 1});
        dc.SetBrush(wxNullBrush);
    }
}

void BackgroundImageCanvas::_OnSize(wxSizeEvent& event) {
    this->OnSize(event);
    event.Skip();
}

}  // namespace Utils
