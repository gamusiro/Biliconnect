// ATLヘッダをインクルード
#include <atlconv.h>

#include "StringConverter.h"

// ATLスタティックリンクライブラリをリンク
#pragma comment(lib, "atls.lib")
// #pragma comment(lib, "afxnmcd.lib")


// string -> wstring変換
void StringConverter::StrToStrW(std::wstring& buffer, const std::string& origin)
{
	// ATLの変換マクロを展開
    USES_CONVERSION_EX;

    // A2W_EX汎用変換マクロを使いstd::string(CHAR)->std::wstring(WCHAR)変換
    const LPWSTR pwstr = A2W_EX(origin.c_str(), origin.length());
    if (pwstr != NULL) {
        buffer = pwstr;
    }
}

// wtring -> string
void StringConverter::StrWToStr(std::string& buffer, const std::wstring& origin)
{
    // ATLの変換マクロを展開
    USES_CONVERSION_EX;

    // A2W_EX汎用変換マクロを使いstd::string(CHAR)->std::wstring(WCHAR)変換
    const LPSTR pwstr = W2A_EX(origin.c_str(), origin.length());
    if (pwstr != NULL) {
        buffer = pwstr;
    }
}

// const char -> wchar
void StringConverter::CptrToCWstr(wchar_t* buffer, const char* string, size_t bufferSize)
{
    // ATLの変換マクロを展開
    USES_CONVERSION_EX;

    const LPWSTR pwstr = A2W_EX(string, bufferSize);
    if (pwstr != NULL) {
        memcpy(buffer, pwstr, bufferSize);
    }
}

// wchar -> char
void StringConverter::CWStrToCptr(char* buffer, const wchar_t* string, size_t bufferSize)
{
    // ATLの変換マクロを展開
    USES_CONVERSION_EX;

    const LPSTR pwstr = W2A_EX(string, bufferSize);
    if (pwstr != NULL) {
        memcpy(buffer, pwstr, bufferSize);
    }
}
