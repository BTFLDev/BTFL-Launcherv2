#ifndef __MODEL_ASSET_HPP__
#define __MODEL_ASSET_HPP__

namespace Model::Asset {

enum class Icon {
    DISCORD,
    REDDIT,
    TWITTER,
    WEBSITE,
    YOUTUBE,
};

enum class Material {
    TEXT_BOTTOM_SHADOW,
};

enum class Shape {
    MAIN_FRAME,
};

enum class Font {
    LORA,
};

namespace Image {

enum class Plain {
};

enum class Encrypted {
    CAULDRON,
    DEVIL,
    PHOENIX,
    ROC,
    SIRIUS,
    SPIDER,
    WORM,
};

};  // namespace Image

}  // namespace Model::Asset

#endif  // __MODEL_ASSET_HPP__
