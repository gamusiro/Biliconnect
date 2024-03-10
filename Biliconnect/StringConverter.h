#pragma once

#include <string>

class StringConverter
{
public:
	/*
	* @ brief \
	*	string ���� wstring
	* @ param \
	*	buffer	: �󂯎��^
	*	string	: ���f�[�^
	*/
	static void StrToStrW(std::wstring& buffer, const std::string& string);

	/*
	* @ brief \
	*	wstring ���� string
	* @ param \
	*	buffer	: �󂯎��^
	*	string	: ���f�[�^
	*/
	static void StrWToStr(std::string& buffer, const std::wstring& string);

	/*
	* @ brief \
	*	const char ���� wchar
	* @ param \
	*	buffer		: �󂯎��^
	*	string		: ���f�[�^
	*	bufferSize	: �o�b�t�@�̑傫��(�o�b�t�@���傫���ƃG���[�ɂȂ�)
	*/
	static void CptrToCWstr(wchar_t* buffer, const char* string, size_t bufferSize);

	/*
	* @ brief \
	*	const wchar_t ���� char
	* @ param \
	*	buffer		: �󂯎��^
	*	string		: ���f�[�^
	*	bufferSize	: �o�b�t�@�̑傫��(�o�b�t�@���傫���ƃG���[�ɂȂ�)
	*/
	static void CWStrToCptr(char* buffer, const wchar_t* string, size_t bufferSize);
};

