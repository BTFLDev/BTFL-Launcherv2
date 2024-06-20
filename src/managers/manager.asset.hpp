#ifndef __MANAGER_ASSET_HPP__
#define __MANAGER_ASSET_HPP__

#include <wx/bmpbndl.h>
#include <wx/filename.h>
#include <wx/string.h>

#include "models/model.asset.hpp"

namespace Manager {

class Asset {
public:
    Asset(const Asset &other) = delete;

    static wxBitmapBundle GetIcon(Model::Asset::Icon icon, const wxSize &size);
    static wxBitmapBundle GetMaterial(Model::Asset::Material material, const wxSize &size);
    static wxBitmap GetShape(Model::Asset::Shape shape);
    static wxBitmap GetPlainImage(Model::Asset::Image::Plain image);
    static wxBitmap GetEncryptedImage(Model::Asset::Image::Encrypted image);

    inline static void SetAssetsPath(const wxString &path) {
        if (path.EndsWith("/")) {
            Instance().m_sAssetPath = path;
        } else {
            Instance().m_sAssetPath = path + "/";
        }
    }
    inline static wxFileName GetAssetsPath() { return wxFileName{Instance().m_sAssetPath}; }

    inline static Asset &Instance() {
        static Asset sInstance;
        return sInstance;
    }

private:
    Asset() = default;

    static wxString GetIconPath(Model::Asset::Icon icon);
    static wxString GetMaterialPath(Model::Asset::Material material);
    static wxString GetShapePath(Model::Asset::Shape shape);
    static wxString GetPlainImagePath(Model::Asset::Image::Plain image);
    static wxString GetEncryptedImagePath(Model::Asset::Image::Encrypted image);

    static void InitializeHandlers();

private:
    wxString m_sAssetPath = wxEmptyString;
};

}  // namespace Manager

#endif  // __MANAGER_ASSET_HPP__
