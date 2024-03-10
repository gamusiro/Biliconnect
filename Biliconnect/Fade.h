/*=========================================================================
	Date : 2021/12/21(��)	Fade.h
		Author : ���ނ��邧
		Update :
=========================================================================*/
#ifndef FADE_H_
#define FADE_H_

#include "main.h"
#include "SceneManager.h"

//�V�[���̃^�C�v
enum class FADE_MODE
{
	NONE,
	FADE_IN,
	FADE_OUT
};

//�V�[���̃^�C�v
enum class FADE_TYPE
{
	ALPHA,
	STRIPE,
	DIAMOND,
	STAIR,
	MASK,
	CHAN
};


class Application;
class Texture;

class Fade
{
public:
	static void Init(Application* app);	//����������
	static void Uninit();				//�I������
	static void Update();				//�X�V����
	static void Draw();					//�`�揈��

public:
	/*
	* @ brief
	*		�V�[���J��
	* @ param
	*		next		: ���̃V�[����
	*		type		: �t�F�[�h�^�C�v
	*		rgb			: �t�F�[�h���g��
	*		waitFrame	: �t�F�[�h�C������܂ł̑҂��t���[����
	*/
	static void Transition(
		SCENE_TYPE next,
		FADE_TYPE type,
		const Texture* texture = nullptr,
		math::Float3 rgb = math::Float3(26.0f / 255.0f, 7.0f / 255.0f, 80.0f / 255.0f),
		UINT waitFrame = 0);

	/*
	* @ brief
	*		�t�F�[�h���Ă��Ȃ����
	* @ return
	*		true	: �t�F�[�h���ĂȂ�
	*/
	static bool GetState();

private:
	static void DrawAlpha();
	static void DrawStripe();
	static void DrawDiamond();
	static void DrawStair();
	static void DrawTexture();
	static void DrawChan();

private:
	static Application* m_Application;
	static FADE_MODE	m_Mode;
	static FADE_TYPE	m_Type;
	static SCENE_TYPE	m_Next;
	static math::Float4	m_Color;
	static UINT			m_WaitFrame;
	static UINT			m_CountFrame;
	static Texture		m_Texture;
};

#endif // !FADE_H_
