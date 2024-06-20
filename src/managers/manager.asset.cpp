#include "managers/manager.asset.hpp"

#include <wx/gdicmn.h>
#include <wx/image.h>
#include <wx/imagpng.h>
#include <wx/msgdlg.h>
#include <wx/mstream.h>
#include <wx/wfstream.h>

#include "utils/crypto.hpp"

namespace Manager {

wxBitmapBundle Asset::GetIcon(Model::Asset::Icon icon, const wxSize &size) {
    return wxBitmapBundle::FromSVGFile(GetIconPath(icon), size);
}

wxBitmapBundle Asset::GetMaterial(Model::Asset::Material material, const wxSize &size) {
    return wxBitmapBundle::FromSVGFile(GetMaterialPath(material), size);
}

wxBitmap Asset::GetShape(Model::Asset::Shape shape) {
    InitializeHandlers();
    return wxBitmap(GetShapePath(shape), wxBITMAP_TYPE_PNG);
}

wxBitmap Asset::GetPlainImage(Model::Asset::Image::Plain image) {
    InitializeHandlers();
    return wxBitmap(GetPlainImagePath(image), wxBITMAP_TYPE_JPEG);
}

wxBitmap Asset::GetEncryptedImage(Model::Asset::Image::Encrypted image) {
    InitializeHandlers();
    wxString path = GetEncryptedImagePath(image);
    wxFFileInputStream fstream(path);

    wxFileOffset streamSize = fstream.GetLength();
    char *data = new char[streamSize];

    for (int i = 0; i < streamSize; i++) {
        char ch;
        fstream.Read(&ch, 1);
        data[i] = Utils::Crypto::DecryptChar(ch, i);
    }

    wxMemoryInputStream memStream(data, streamSize);
    wxBitmap bmp(memStream, wxBITMAP_TYPE_JPEG);
    delete[] data;

    return bmp;
}

wxString Asset::GetIconPath(Model::Asset::Icon icon) {
    wxFileName path = GetAssetsPath();

    switch (icon) {
        case Model::Asset::Icon::DISCORD:
            path.SetFullName("Discord.svg");
            break;
        case Model::Asset::Icon::REDDIT:
            path.SetFullName("Reddit.svg");
            break;
        case Model::Asset::Icon::TWITTER:
            path.SetFullName("Twitter.svg");
            break;
        case Model::Asset::Icon::WEBSITE:
            path.SetFullName("Website.svg");
            break;
        case Model::Asset::Icon::YOUTUBE:
            path.SetFullName("YouTube.svg");
            break;
    }

    return path.GetFullPath();
}

wxString Asset::GetMaterialPath(Model::Asset::Material material) {
    wxFileName path = GetAssetsPath();

    switch (material) {
        case Model::Asset::Material::TEXT_BOTTOM_SHADOW:
            path.SetFullName("TextBottomShadow.svg");
            break;
    }

    return path.GetFullPath();
}

wxString Asset::GetShapePath(Model::Asset::Shape shape) {
    wxFileName path = GetAssetsPath();

    switch (shape) {
        case Model::Asset::Shape::MAIN_FRAME:
            path.SetFullName("main_frame.png");
            break;
    }

    return path.GetFullPath();
}

wxString Asset::GetPlainImagePath(Model::Asset::Image::Plain image) {
    wxFileName path = GetAssetsPath();

    switch (image) {}

    return path.GetFullPath();
}

wxString Asset::GetEncryptedImagePath(Model::Asset::Image::Encrypted image) {
    wxFileName path = GetAssetsPath();

    switch (image) {
        case Model::Asset::Image::Encrypted::CAULDRON:
            path.SetFullName("cauldron.jpg");
            break;
        case Model::Asset::Image::Encrypted::DEVIL:
            path.SetFullName("devil.png");
            break;
        case Model::Asset::Image::Encrypted::PHOENIX:
            path.SetFullName("phoenix.jpg");
            break;
        case Model::Asset::Image::Encrypted::ROC:
            path.SetFullName("roc.jpg");
            break;
        case Model::Asset::Image::Encrypted::SIRIUS:
            path.SetFullName("sirius.jpg");
            break;
        case Model::Asset::Image::Encrypted::SPIDER:
            path.SetFullName("spider.jpg");
            break;
        case Model::Asset::Image::Encrypted::WORM:
            path.SetFullName("worm.jpg");
            break;
    }

    return path.GetFullPath();
}

void Asset::InitializeHandlers() {
    static bool bDidInitialize = false;

    if (bDidInitialize) {
        return;
    }

    wxInitAllImageHandlers();
    bDidInitialize = true;
}

}  // namespace Manager
