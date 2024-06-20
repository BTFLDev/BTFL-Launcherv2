#ifndef __STYLE_COLOR_HPP__
#define __STYLE_COLOR_HPP__

#include <wx/colour.h>

namespace Style::Color {

inline const wxColour Clear() { return wxColour(0, 0, 0, 0); }
inline const wxColour Black(unsigned char alpha = 255) { return wxColour(0, 0, 0, alpha); }
inline const wxColour TextGrey(unsigned char alpha = 255) { return wxColour(122, 122, 122, alpha); }
inline const wxColour TextDarkGrey(unsigned char alpha = 255) {
    return wxColour(102, 102, 102, alpha);
}
inline const wxColour TextSuperLightGrey(unsigned char alpha = 255) {
    return wxColour(230, 230, 230, alpha);
}
inline const wxColour White(unsigned char alpha = 255) { return wxColour(255, 255, 255, alpha); }
inline const wxColour Turquoise(unsigned char alpha = 255) { return wxColour(67, 199, 217, alpha); }

}  // namespace Style::Color

#endif  // __STYLE_COLOR_HPP__
