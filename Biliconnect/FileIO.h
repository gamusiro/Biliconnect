/*
*	Date : 2022/03/29
*		Author : がむしるぉ
*		Update : ----/--/--
* 
*	ファイル読み込み(バイナリーオープン)
*/
#pragma once
#ifndef FILEIO_H_
#define FILEIO_H_

#include <string>

class FileIO
{
public:
	FileIO() :m_Success(false) {}
	FileIO(std::string& buffer, const std::string& fileName, bool read = true);
	~FileIO() {}

public:
	/*
	* @ brief /
	*	ファイルの読み込みを行います。
	* @ param /
	*	buffer	: 読み込んだデータ格納変数
	*	fileName: 開くファイルの名前
	* @ return /
	*	true	: 正常に処理された
	*	false	: それ以外
	*/
	bool Load(std::string& buffer, const std::string& fileName);

	/*
	* @ brief /
	*	ファイルの書き込みを行います。
	* @ param /
	*	buffer	: 読み込んだデータ格納変数
	*	fileName: 開くファイルの名前
	* @ return /
	*	true	: 正常に処理された
	*	false	: それ以外
	*/
	bool Write(std::string& buffer, const std::string& fileName);

	/*
	* @ brief /
	* 
	*/
	bool Fail();

private:
	bool m_Success;
};
#endif // !FILEIO_H_

