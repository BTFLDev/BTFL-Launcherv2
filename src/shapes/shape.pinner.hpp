#ifndef __SHAPE_PINNER_HPP__
#define __SHAPE_PINNER_HPP__

#include <wx/gdicmn.h>

#include <vector>

namespace Shape {

class Pinner;

enum class PinPoint {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,

    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
};

enum class PinStyle {
    IN,
    OUT,
};

struct Pin {
    Pinner* pinned;
    PinPoint pinnedPoint;
    PinPoint pinPoint;
    wxRealPoint offset;
};

class Pinner {
public:
    virtual void MoveTo(const wxRealPoint& point) = 0;
    virtual wxRealPoint GetPosition() = 0;
    virtual wxRealPoint GetSize() = 0;

    virtual bool Pin(Pinner* pinned, PinPoint pinnedPoint, PinPoint pinPoint, wxRealPoint offset);
    virtual bool PinTo(Pinner* pinner, PinPoint pinnedPoint, PinPoint pinPoint, wxRealPoint offset);
    virtual void Unpin(Pinner* pinned);
    virtual void UnpinFrom(Pinner* pinner);

    virtual void LayoutPins();

private:
    static wxRealPoint GetPinRealPoint(const wxRealPoint& pos, const wxRealPoint& size, PinPoint pinPoint);
    static wxRealPoint GetPinnedRealPointOffset(const wxRealPoint& pinnedSize, PinPoint pinnedPoint);

    static bool _DoPin(
        Pinner* pinner,
        Pinner* pinned,
        PinPoint pinnedPoint,
        PinPoint pinPoint,
        wxRealPoint offset
    );
    static void _DoUnpin(Pinner* pinner, Pinner* pinned);

private:
    Pinner* pPinnedTo;
    std::vector<Shape::Pin> vPins;
};

}  // namespace Shape

#endif  // __SHAPE_PINNER_HPP__
