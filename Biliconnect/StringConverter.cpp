// ATL�w�b�_���C���N���[�h
#include <atlconv.h>

#include "StringConverter.h"

// ATL�X�^�e�B�b�N�����N���C�u�����������N
#pragma comment(lib, "atls.lib")
// #pragma comment(lib, "afxnmcd.lib")


// string -> wstring�ϊ�
void StringConverter::StrToStrW(std::wstring& buffer, const std::string& origin)
{
	// ATL�̕ϊ��}�N����W�J
    USES_CONVERSION_EX;

    // A2W_EX�ėp�ϊ��}�N�����g��std::string(CHAR)->std::wstring(WCHAR)�ϊ�
    const LPWSTR pwstr = A2W_EX(origin.c_str(), origin.length());
    if (pwstr != NULL) {
        buffer = pwstr;
    }
}

// wtring -> string
void StringConverter::StrWToStr(std::string& buffer, const std::wstring& origin)
{
    // ATL�̕ϊ��}�N����W�J
    USES_CONVERSION_EX;

    // A2W_EX�ėp�ϊ��}�N�����g��std::string(CHAR)->std::wstring(WCHAR)�ϊ�
    const LPSTR pwstr = W2A_EX(origin.c_str(), origin.length());
    if (pwstr != NULL) {
        buffer = pwstr;
    }
}

// const char -> wchar
void StringConverter::CptrToCWstr(wchar_t* buffer, const char* string, size_t bufferSize)
{
    // ATL�̕ϊ��}�N����W�J
    USES_CONVERSION_EX;

    const LPWSTR pwstr = A2W_EX(string, bufferSize);
    if (pwstr != NULL) {
        memcpy(buffer, pwstr, bufferSize);
    }
}

// wchar -> char
void StringConverter::CWStrToCptr(char* buffer, const wchar_t* string, size_t bufferSize)
{
    // ATL�̕ϊ��}�N����W�J
    USES_CONVERSION_EX;

    const LPSTR pwstr = W2A_EX(string, bufferSize);
    if (pwstr != NULL) {
        memcpy(buffer, pwstr, bufferSize);
    }
}
