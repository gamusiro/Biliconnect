/*=========================================================================
	Date : 2021/12/21(��)	Title.h
		Author : ���ނ��邧
		Update :
=========================================================================*/
#ifndef TITLE_H_
#define TITLE_H_

//������C���N���[�h����
#include "GameCreateSystem.h"
#include "SceneInterface.h"

class BGMOption;

class Title : public SceneInterface
{
public:
	Title();
	~Title();

public:
	void Init();	//����������
	void Uninit();	//�I������
	void Update();	//�X�V����
	void Draw();	//�`�揈��
	void GameStart();

private:
	BGMOption* m_BGMOption;
	BGM* m_BGM;

	//�e�N�X�`��
	enum {
		BG,
		TITLE_LOGO,
		CREDIT,
		EXIT,
		CREDIT_BUTTON,
		PRESS_B,
		START,
		OPTION,
		FADE,
		FRAME,
		MAX,
	};

	//���[�h
	typedef enum {
		MODE_1,
		MODE_2,
		MODE_3,
		MODE_4,
	}MODE;

	//�I������
	typedef enum {
		S_START,
		S_OPTION,
	}SELECT;



	
	Texture*  	 m_Tex[MAX];
	math::Float2 m_Pos[MAX], m_Vel[MAX], m_Size[MAX];
	math::Float4 m_Color[MAX];
	bool         m_Use[MAX];
	int          m_Frame;
	
	//���[�h�Ǘ�
	int m_ModeFrame;
	MODE m_Mode;


	//Press�{�^���̓_��
	int m_BlinkingFrame;
	float m_isBlinkingSpd, m_BlinkingMagnitude, m_Rarefaction;
	bool m_isBlinking;

	//�I������
	SELECT m_Select;

	//�N���W�b�g�\��
	bool DisplayCredit;

	bool canTransit;

	constexpr static int MASTER_VOLUME = 6;	// �}�X�^�[�{�����[��
	bool first;
};

#endif // !TITLE_H_


