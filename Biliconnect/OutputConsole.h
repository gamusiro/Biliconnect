/*=========================================================================
	Date : 2021/01/21(��)	OutputConsole.h
		Author	: ���ނ��邧
		Update	:
		Comment	:
		���Ö{���̎����f�[�^���ȈՓI�ɗ��p�����炷(Living)
=========================================================================*/
#ifndef OUTPUTCONSOLE_H_
#define OUTPUTCONSOLE_H_

#include <stdio.h>
#include <Windows.h>

class OutputConsole
{
public:
	void Init();	//����������
	void Uninit();	//�I������
	void Update();	//�X�V����
	void Clear();	//�R���\�[���E�B���h�E�̃N���A����

private:
	FILE*	m_Output;		
	HANDLE	m_Console;		//�R���\�[���̃n���h��
	COORD	m_CurosrPos;	//�R���\�[�����̃J�[�\���|�W�V����
};

#endif // !OUTPUTCONSOLE_H_

