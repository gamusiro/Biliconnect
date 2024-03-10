/*=========================================================================
	Date : 2021/11/28(��)	Window.h
		Author	: ���ނ��邧
		Update	: 2022/02/05(�y)
		Comment	:
		���E�B���h�E��ʂ̃N���X
=========================================================================*/
#ifndef WINDOW_H_
#define WINDOW_H_


#define WINDOW_SIZE_WIDTH  960
#define WINDOW_SIZE_HEIGHT 540

#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

public:
	//�E�B���h�E�̓o�^���s��
	int  Init	(HINSTANCE hInstance, const LPCSTR& class_name);	
	//�E�B���h�E�̏I������
	void Uninit	();													

public:
	//��ʂ̐�������
	//�E�B���h�E���O��\�����Ȃ��ꍇ�͋�
	void Create	(const LPCSTR& window_name);		
	//��ʂ̕\������
	void Show	(int nCmdShow);
	//��ʂ̊Ǘ����s��
	bool Dispatcher();

	// �E�B���h�E���Q�[����c�񂦕���
	void Exit();
public:
	HWND	Get_HWND()	{ return m_hwnd; }
	LPCSTR	Get_Title() { return m_windowTitle; }

private:
	HINSTANCE	m_instance;			//�o�^���̃E�B���h�E�̃C���X�^���X��o�^���Ă���
	LPCSTR		m_className;		//�E�B���h�E�N���X�̖��O��o�^���Ă���
	LPCSTR		m_windowTitle;		//�o�[�ɕ\�����閼�O��ێ����Ă���
	HWND		m_hwnd;				//�E�B���h�E�n���h���̃f�[�^��ێ����Ă���
	MSG			m_message;			//���b�Z�[�W��ێ����Ă���
};

#endif // !WINDOW_H_
