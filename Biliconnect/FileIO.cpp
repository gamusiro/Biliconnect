/*
*	Date : 2022/03/29
*		Author : ���ނ��邧
*		Update : ----/--/--
*
*	�t�@�C���ǂݍ���(�o�C�i���[�I�[�v��)
*/
#include "FileIO.h"

#include <fstream>

// �R���X�g���N�^
FileIO::FileIO(std::string& buffer, const std::string& fileName, bool read)
	:m_Success(false)
{
	if (read)
		this->Load(buffer, fileName);
	else
		this->Write(buffer, fileName);
}

/*
* �t�@�C���f�[�^��ǂݍ���
*/
bool FileIO::Load(std::string& buffer, const std::string& fileName)
{
	// �o�C�i���[�I�[�v��
	std::ifstream ifs(fileName, std::ios::binary);
	if (ifs.fail())
	{// �t�@�C�����J���̂Ɏ��s
		return m_Success = false;
	}

	ifs.seekg(0, std::ios::end);	// �|�C���^�𖖔��Ɉړ�
	buffer.resize(ifs.tellg());		// �o�b�t�@���f�[�^�T�C�Y�Ɋg������
	ifs.seekg(0, std::ios::beg);	// �|�C���^��擪�Ɉړ�

	ifs.read(&buffer[0], buffer.size());	// �f�[�^��ǂݍ���

	// �t�@�C�������
	ifs.close();
	return m_Success = true;
}

/*
* �t�@�C���f�[�^����������
*/
bool FileIO::Write(std::string& buffer, const std::string& fileName)
{
	std::ofstream ofs(fileName, std::ios::out);
	if (ofs.fail())
	{// �t�@�C���̍쐬�Ɏ��s
		return m_Success = false;
	}

	// ��������
	ofs << buffer << std::endl;
	
	// �t�@�C�������
	ofs.close();
	return m_Success = true;
}

/*
* �t�@�C�����J���������ׂ�
*/
bool FileIO::Fail()
{
	return !m_Success;
}
