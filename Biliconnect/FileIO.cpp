/*
*	Date : 2022/03/29
*		Author : がむしるぉ
*		Update : ----/--/--
*
*	ファイル読み込み(バイナリーオープン)
*/
#include "FileIO.h"

#include <fstream>

// コンストラクタ
FileIO::FileIO(std::string& buffer, const std::string& fileName, bool read)
	:m_Success(false)
{
	if (read)
		this->Load(buffer, fileName);
	else
		this->Write(buffer, fileName);
}

/*
* ファイルデータを読み込む
*/
bool FileIO::Load(std::string& buffer, const std::string& fileName)
{
	// バイナリーオープン
	std::ifstream ifs(fileName, std::ios::binary);
	if (ifs.fail())
	{// ファイルを開くのに失敗
		return m_Success = false;
	}

	ifs.seekg(0, std::ios::end);	// ポインタを末尾に移動
	buffer.resize(ifs.tellg());		// バッファをデータサイズに拡張する
	ifs.seekg(0, std::ios::beg);	// ポインタを先頭に移動

	ifs.read(&buffer[0], buffer.size());	// データを読み込む

	// ファイルを閉じる
	ifs.close();
	return m_Success = true;
}

/*
* ファイルデータを書き込む
*/
bool FileIO::Write(std::string& buffer, const std::string& fileName)
{
	std::ofstream ofs(fileName, std::ios::out);
	if (ofs.fail())
	{// ファイルの作成に失敗
		return m_Success = false;
	}

	// 書き込む
	ofs << buffer << std::endl;
	
	// ファイルを閉じる
	ofs.close();
	return m_Success = true;
}

/*
* ファイルが開けたか調べる
*/
bool FileIO::Fail()
{
	return !m_Success;
}
