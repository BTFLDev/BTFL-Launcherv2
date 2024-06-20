#ifndef __MODEL_SOCIALMEDIA_HPP__
#define __MODEL_SOCIALMEDIA_HPP__

#include <vector>

namespace Model {

enum class SocialMedia {
    DISCORD,
    REDDIT,
    TWITTER,
    WEBSITE,
    YOUTUBE
};

inline std::vector<SocialMedia> AllSocialMediaCases() {
    return {
        SocialMedia::DISCORD,
        SocialMedia::REDDIT,
        SocialMedia::TWITTER,
        SocialMedia::WEBSITE,
        SocialMedia::YOUTUBE
    };
}

}  // namespace Model

#endif  // __MODEL_SOCIALMEDIA_HPP__
