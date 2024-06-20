#ifndef __COLOUR_HPP__
#define __COLOUR_HPP__

#include <wx/colour.h>

namespace Utils {

wxColour MixColours(const wxColour& firstColour, const wxColour& secondColour, int percent) {
    int newRed =
        (double)((secondColour.Red() * percent) + (firstColour.Red() * (100 - percent))) / 100;
    int newGreen =
        (double)((secondColour.Green() * percent) + (firstColour.Green() * (100 - percent))) / 100;
    int newBlue =
        (double)((secondColour.Blue() * percent) + (firstColour.Blue() * (100 - percent))) / 100;

    return wxColour((unsigned char)newRed, (unsigned char)newGreen, (unsigned char)newBlue);
}

}  // namespace Utils

#endif
