#include "views/view.home.hpp"

#include <wx/msgdlg.h>

#include <optional>

#include "managers/manager.asset.hpp"
#include "managers/manager.screen.hpp"
#include "models/model.asset.hpp"
#include "models/model.screen.hpp"
#include "shapes/shape.action_button.hpp"
#include "shapes/shape.ids.hpp"
#include "shapes/shape.pinner.hpp"
#include "utils/background_image_canvas.hpp"

namespace View {

Home::Home(wxWindow* parent, wxSFDiagramManager* manager, ViewModel::Home* viewModel) {
    this->Create(parent, manager, viewModel);
}

Home::~Home() { delete this->pViewModel; }

void Home::Create(wxWindow* parent, wxSFDiagramManager* manager, ViewModel::Home* viewModel) {
    wxLogDebug("View/Home: Initializing");
    Utils::BackgroundImageCanvas::Create(
        parent,
        manager,
        {
            Manager::Asset::GetEncryptedImage(Model::Asset::Image::Encrypted::ROC),
            Manager::Asset::GetEncryptedImage(Model::Asset::Image::Encrypted::CAULDRON),
            Manager::Asset::GetEncryptedImage(Model::Asset::Image::Encrypted::PHOENIX),
            Manager::Asset::GetEncryptedImage(Model::Asset::Image::Encrypted::WORM),
            Manager::Asset::GetEncryptedImage(Model::Asset::Image::Encrypted::SIRIUS),
            Manager::Asset::GetEncryptedImage(Model::Asset::Image::Encrypted::SPIDER),
        },
        true,
        true
    );

    this->pViewModel = viewModel;

    this->RemoveStyle(sfsMULTI_SELECTION);
    this->RemoveStyle(sfsPROCESS_MOUSEWHEEL);
    this->SetHoverColour(Style::Color::White());

    this->pMainButton = new Shape::ActionButton(
        &this->pViewModel->mainButtonText,
        &this->pViewModel->mainButtonState,
        this->pViewModel->mainButtonFont,
        wxDefaultPosition,
        wxDefaultPosition,
        Constants::MainButtonCornerRadius(),
        manager,
        &this->pViewModel->settingsButtonIcon
    );
    manager->AddShape(this->pMainButton, nullptr, wxDefaultPosition, true, false);
    this->pMainButton->SetId(int(Shape::IDs::MAIN_BUTTON));

    this->pSettingsButton = new Shape::ActionButton(
        &this->pViewModel->settingsButtonText,
        &this->pViewModel->settingsButtonState,
        this->pViewModel->settingsButtonFont,
        wxDefaultPosition,
        wxDefaultPosition,
        Constants::MainButtonCornerRadius(),
        manager,
        &this->pViewModel->settingsButtonIcon,
        std::nullopt,
        &this->pViewModel->settingsButtonYPadding,
        &this->pViewModel->settingsButtonXPadding
    );
    manager->AddShape(this->pSettingsButton, nullptr, wxDefaultPosition, true, false);
    this->pSettingsButton->SetId(int(Shape::IDs::SETTINGS_BUTTON));

    this->watch(Manager::Screen::GetScreenSource());

    this->BindEvents();
    this->PinButtons();
}

void Home::subject_updated(const gaze::subject* subj) {
    this->CallAfter([this]() { this->LayoutPins(); });
}

void Home::BindEvents() {
    wxLogDebug("View/Home: Binding events");
    Bind(wxEVT_SIZE, &Home::OnSize, this);
    Bind(wxEVT_SF_SHAPE_LEFT_DOWN, &Home::OnMainButtonClick, this, int(Shape::IDs::MAIN_BUTTON));
    Bind(
        wxEVT_SF_SHAPE_LEFT_DOWN,
        &Home::OnSettingsButtonClick,
        this,
        int(Shape::IDs::SETTINGS_BUTTON)
    );
}

void Home::OnMainButtonClick(wxSFShapeMouseEvent& event) {
    wxLogDebug("View/Home: Main Button clicked");
    wxMessageBox("hello");
}

void Home::OnSettingsButtonClick(wxSFShapeMouseEvent& event) {
    wxLogDebug("View/Home: Settings Button clicked. Will Change screen to secondary");
    Manager::Screen::SetScreen(Model::Screen::SECONDARY);
}

void Home::OnSize(wxSizeEvent& event) {
    wxLogDebug("View/Home: OnSize called. Laying out pins");
    this->LayoutPins();
    event.Skip();
}

void Home::PinButtons() {
    wxLogDebug("View/Home: Pinning buttons");
    this->Pin(
        this->pMainButton,
        Shape::PinPoint::BOTTOM_LEFT,
        Shape::PinPoint::BOTTOM_LEFT,
        Constants::MainButtonOffset()
    );
    this->pSettingsButton->PinTo(
        this->pMainButton,
        Shape::PinPoint::LEFT,
        Shape::PinPoint::RIGHT,
        Constants::SettingsButtonOffset()
    );
}

}  // namespace View
