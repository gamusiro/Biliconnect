#pragma once

#include <string>

class StringConverter
{
public:
	/*
	* @ brief \
	*	string から wstring
	* @ param \
	*	buffer	: 受け取る型
	*	string	: 元データ
	*/
	static void StrToStrW(std::wstring& buffer, const std::string& string);

	/*
	* @ brief \
	*	wstring から string
	* @ param \
	*	buffer	: 受け取る型
	*	string	: 元データ
	*/
	static void StrWToStr(std::string& buffer, const std::wstring& string);

	/*
	* @ brief \
	*	const char から wchar
	* @ param \
	*	buffer		: 受け取る型
	*	string		: 元データ
	*	bufferSize	: バッファの大きさ(バッファより大きいとエラーになる)
	*/
	static void CptrToCWstr(wchar_t* buffer, const char* string, size_t bufferSize);

	/*
	* @ brief \
	*	const wchar_t から char
	* @ param \
	*	buffer		: 受け取る型
	*	string		: 元データ
	*	bufferSize	: バッファの大きさ(バッファより大きいとエラーになる)
	*/
	static void CWStrToCptr(char* buffer, const wchar_t* string, size_t bufferSize);
};

