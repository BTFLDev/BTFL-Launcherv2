#include "screens/screen.launcher_secondary.hpp"

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

#include "managers/manager.asset.hpp"
#include "style/style.color.hpp"

namespace Screen {

void LauncherSecondary::Create(wxWindow* parent, wxSFDiagramManager* manager) {
    Utils::BackgroundImageCanvas::Create(
        parent,
        manager,
        {Manager::Asset::GetEncryptedImage(Model::Asset::Image::Encrypted::DEVIL)},
        false,
        false
    );

    this->RemoveStyle(sfsMULTI_SELECTION);
    this->RemoveStyle(sfsPROCESS_MOUSEWHEEL);

    this->SetBackgroundColour(Style::Color::Black());
}

}  // namespace Screen
