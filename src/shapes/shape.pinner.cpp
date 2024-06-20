#include "shapes/shape.pinner.hpp"

#include <wx/msgdlg.h>

#include <string>

namespace Shape {

bool Pinner::Pin(Pinner* pinned, PinPoint pinnedPoint, PinPoint pinPoint, wxRealPoint offset) {
    return Pinner::_DoPin(this, pinned, pinnedPoint, pinPoint, offset);
}

bool Pinner::PinTo(Pinner* pinner, PinPoint pinnedPoint, PinPoint pinPoint, wxRealPoint offset) {
    return Pinner::_DoPin(pinner, this, pinnedPoint, pinPoint, offset);
}

void Pinner::Unpin(Pinner* pinned) { Pinner::_DoUnpin(this, pinned); }

void Pinner::UnpinFrom(Pinner* pinner) { Pinner::_DoUnpin(pinner, this); }

bool Pinner::_DoPin(
    Pinner* pinner,
    Pinner* pinned,
    PinPoint pinnedPoint,
    PinPoint pinPoint,
    wxRealPoint offset
) {
    if (pinned->pPinnedTo == pinner) {
        return false;
    }

    if (pinned->pPinnedTo != nullptr) {
        pinned->UnpinFrom(pinned->pPinnedTo);
    }

    pinner->vPins.push_back({pinned, pinnedPoint, pinPoint, offset});
    pinned->pPinnedTo = pinner;
    return true;
}

void Pinner::_DoUnpin(Pinner* pinner, Pinner* pinned) {
    if (pinned->pPinnedTo != pinner) {
        return;
    }

    for (int i = 0; i < pinner->vPins.size(); i++) {
        if (pinner->vPins[i].pinned != pinned) {
            continue;
        }

        pinner->vPins.erase(pinner->vPins.begin() + i);
        break;
    }

    pinned->pPinnedTo = nullptr;
}

void Pinner::LayoutPins() {
    const wxRealPoint pos = this->GetPosition();
    const wxRealPoint size = this->GetSize();

    for (Shape::Pin pin : this->vPins) {
        wxRealPoint pinPoint = Pinner::GetPinRealPoint(pos, size, pin.pinPoint);
        wxRealPoint pinnedPointOffset =
            Pinner::GetPinnedRealPointOffset(pin.pinned->GetSize(), pin.pinnedPoint);

        wxRealPoint finalPoint = pinPoint + pinnedPointOffset + pin.offset;
        pin.pinned->MoveTo(finalPoint);
        pin.pinned->LayoutPins();
    }
}

wxRealPoint
Pinner::GetPinRealPoint(const wxRealPoint& pos, const wxRealPoint& size, PinPoint pinPoint) {
    wxRealPoint refPoint;
    switch (pinPoint) {
        case PinPoint::LEFT:
            refPoint = {pos.x, pos.y + (size.y / 2)};
            break;
        case PinPoint::RIGHT:
            refPoint = {pos.x + size.x, pos.y + (size.y / 2)};
            break;
        case PinPoint::TOP:
            refPoint = {pos.x + (size.x / 2), pos.y};
            break;
        case PinPoint::BOTTOM:
            refPoint = {pos.x + (size.x / 2), pos.y + size.y};
            break;
        case PinPoint::TOP_LEFT:
            refPoint = pos;
            break;
        case PinPoint::TOP_RIGHT:
            refPoint = {pos.x + size.x, pos.y};
            break;
        case PinPoint::BOTTOM_LEFT:
            refPoint = {pos.x, pos.y + size.y};
            break;
        case PinPoint::BOTTOM_RIGHT:
            refPoint = {pos.x + size.x, pos.y + size.y};
            break;
    }

    return refPoint;
}

wxRealPoint Pinner::GetPinnedRealPointOffset(const wxRealPoint& pinnedSize, PinPoint pinnedPoint) {
    wxRealPoint pinnedOffset;
    switch (pinnedPoint) {
        case PinPoint::LEFT:
            pinnedOffset = {0.0, -pinnedSize.y / 2};
            break;
        case PinPoint::RIGHT:
            pinnedOffset = {-pinnedSize.x, -pinnedSize.y / 2};
            break;
        case PinPoint::TOP:
            pinnedOffset = {-pinnedSize.x / 2, 0.0};
            break;
        case PinPoint::BOTTOM:
            pinnedOffset = {-pinnedSize.x / 2, -pinnedSize.y};
            break;
        case PinPoint::TOP_LEFT:
            pinnedOffset = {0.0, 0.0};
            break;
        case PinPoint::TOP_RIGHT:
            pinnedOffset = {-pinnedSize.x, 0.0};
            break;
        case PinPoint::BOTTOM_LEFT:
            pinnedOffset = {0.0, -pinnedSize.y};
            break;
        case PinPoint::BOTTOM_RIGHT:
            pinnedOffset = {-pinnedSize.x, -pinnedSize.y};
            break;
    }

    return pinnedOffset;
}

}  // namespace Shape
