#ifndef __CRYPTO_HPP__
#define __CRYPTO_HPP__

#include <wx/longlong.h>
namespace Utils {

namespace Crypto {

inline char EncryptChar(char ch, wxULongLong code) {
    if (code % 2 == 0)
        ch += 1;
    else if (code % 3 == 0)
        ch += 2;
    else
        ch += 3;

    return ch;
}

inline char DecryptChar(char ch, wxULongLong code) {
    if (code % 2 == 0)
        ch -= 1;
    else if (code % 3 == 0)
        ch -= 2;
    else
        ch -= 3;

    return ch;
}

inline wxString EncryptString(const wxString& str) {
    wxString encryptedString = str;
    for (int i = 0; i < encryptedString.size(); i++)
        encryptedString[i] = EncryptChar(encryptedString[i].GetValue(), i);
    ;

    return encryptedString;
}

inline wxString DecryptString(const wxString& str) {
    wxString decryptedString = str;
    for (int i = 0; i < decryptedString.size(); i++)
        decryptedString[i] = DecryptChar(decryptedString[i].GetValue(), i);

    return decryptedString;
}

}  // namespace crypto

}  // namespace utils

#endif  // __CRYPTO_HPP__
