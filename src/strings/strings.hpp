#ifndef _STRINGS_HPP_
#define _STRINGS_HPP_

#include <wx/intl.h>

namespace Strings {

namespace Frame {

namespace AppMain {

inline wxString Title() { return _("Beyond The Forbidden Lands - Launcher"); }

namespace Menu {

inline wxString Credits() { return _("Credits"); }
inline wxString Help() { return _("Help"); }

}  // namespace Menu

}  // namespace AppMain

}  // namespace Frame

namespace Screen {

namespace LauncherMain {

inline wxString Footer() {
    return _(
        "Beyond the Forbidden Lands is officially classified as a modification of \"Shadow of the "
        "Colossus\" (2005) and ownership of the original game is required to play."
    );
}
inline wxString ReadDisclaimer() { return _("Read disclaimer"); }

}  // namespace LauncherMain

}  // namespace Screen

namespace View {

namespace Home {

inline wxString SelectISO() { return _("SELECT ISO"); }
inline wxString VerifyISO() { return _("VERIFY ISO"); }

}  // namespace Home

}  // namespace View

}  // namespace Strings

#endif  // _STRINGS_HPP_
