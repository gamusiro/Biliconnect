/*
*	Date : 2022/03/29
*		Author : ���ނ��邧
*		Update : ----/--/--
* 
*	�t�@�C���ǂݍ���(�o�C�i���[�I�[�v��)
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
	*	�t�@�C���̓ǂݍ��݂��s���܂��B
	* @ param /
	*	buffer	: �ǂݍ��񂾃f�[�^�i�[�ϐ�
	*	fileName: �J���t�@�C���̖��O
	* @ return /
	*	true	: ����ɏ������ꂽ
	*	false	: ����ȊO
	*/
	bool Load(std::string& buffer, const std::string& fileName);

	/*
	* @ brief /
	*	�t�@�C���̏������݂��s���܂��B
	* @ param /
	*	buffer	: �ǂݍ��񂾃f�[�^�i�[�ϐ�
	*	fileName: �J���t�@�C���̖��O
	* @ return /
	*	true	: ����ɏ������ꂽ
	*	false	: ����ȊO
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

