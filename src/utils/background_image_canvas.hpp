#ifndef __BACKGROUND_IMAGE_CANVAS_HPP__
#define __BACKGROUND_IMAGE_CANVAS_HPP__

#include <wx/bitmap.h>
#include <wx/timer.h>
#include <wx/wxsf/ShapeCanvas.h>

#include "style/style.color.hpp"

namespace Utils {

class BackgroundImageCanvas : public wxSFShapeCanvas {
public:
    BackgroundImageCanvas() {}
    BackgroundImageCanvas(
        wxWindow* parent,
        wxSFDiagramManager* manager,
        std::vector<wxBitmap> backgrounds,
        bool rotate = true,
        bool move = true
    ) {
        this->Create(parent, manager, backgrounds, rotate, move);
    }

    void Create(
        wxWindow* parent,
        wxSFDiagramManager* manager,
        std::vector<wxBitmap> backgrounds,
        bool rotate,
        bool move
    );

    void EnableRotation(bool rotate);

private:
    void BindEvents();

    void DoAnimateBackground();
    void UpdateOverlayColor();
    void UpdateBackgroundPosition();

    inline const wxBitmap& CurrentBackground() const {
        return this->vBackgrounds[this->nCurrentBgIdx];
    }

    void OnSize(wxSizeEvent& event);
    void OnEnterWindow(wxMouseEvent& event);
    void OnLeaveWindow(wxMouseEvent& event);
    void OnBackgroundAnimTimer(wxTimerEvent& event);
    void OnBackgroundChangeTimer(wxTimerEvent& event);
    void OnBackgroundTriggerChangeTimer(wxTimerEvent& event);
    void _OnSize(wxSizeEvent& event);

    virtual void OnMouseMove(wxMouseEvent& event) override;
    virtual void OnUpdateVirtualSize(wxRect& rect) override;
    virtual void DrawBackground(wxDC& dc, bool fromPaint) override;

private:
    std::vector<wxBitmap> vBackgrounds;
    int nCurrentBgIdx = 0;

    wxTimer bgAnimTimer{};
    wxTimer bgChangeTimer{};
    wxTimer bgTriggerChangeTimer{};

    bool bShouldDarkenOverlay = false;
    bool bShouldLightenOverlay = false;
    wxColour overlayColour{Style::Color::Black(Constants::MinOverlayAlpha())};

    bool bBgMoveEnabled = true;
    bool bShouldResetBgPosition = false;
    wxPoint mouseEnterPosition{0, 0};

    float fBgScale = 1.0;

    int nBackgroundX = 0, nBackgroundY = 0, nBackgroundXOffset = 0, nBackgroundYOffset = 0;

private:
    struct Constants {
        constexpr inline static const int MaxBackgroundOffset() { return 30; }
        constexpr inline static const int BgAnimIntervalMs() { return 8; }
        constexpr inline static const int BgChangeIntervalMs() { return 500; }
        constexpr inline static const int BgTriggerChangeIntervalMs() { return 7000; }

        constexpr inline static const int BgPositionResetChange() { return 2; }

        constexpr inline static const unsigned char OverlayAlphaChange() { return 2; }
        constexpr inline static const unsigned char MaxAllowedOverlayAlpha() { return 254; }
        constexpr inline static const unsigned char MaxOverlayAlpha() { return 255; }
        constexpr inline static const unsigned char MinAllowedOverlayAlpha() { return 1; }
        constexpr inline static const unsigned char MinOverlayAlpha() { return 0; }
    };

    enum TimerIDs {
        BG_ANIM,
        BG_CHANGE,
        BG_TRIGGER_CHANGE,
    };
};

}  // namespace Utils

#endif  // __BACKGROUND_IMAGE_CANVAS_HPP__
