/*=========================================================================
	Date : 2021/03/22(��)	MoveChanEffect.h
		Author :
		Update :
=========================================================================*/
#ifndef LINE_EFFECT_H_
#define LINE_EFFECT_H_

#include <memory>
#include "GameCreateSystem.h"
#include "EffectManager.h"
#include "Line.h"

#define LINE_EFFECT_MAX 30
class MoveChan;
class Line;

class LineEffect
{
public:
	LineEffect() = delete;
	LineEffect(math::Float2& movechan,Line* lineptr);
	~LineEffect();
	void Init();
	void Update();
	void Draw();
	void Set();


protected:
	math::Float2&         m_MoveChanPos;
	Line*                 m_LinePtr = nullptr;
//	MOVECHAN_EFFECT_SPEED m_CurSpeed = MOVECHAN_EFFECT_NORMAL;

	int                 m_Frame = 0;//�t���[��
	const int           m_frameToSetMoveChanEffect = 2;//���t���[�����ƂɃZ�b�g���邩
	Texture             m_YellowTex[LINE_EFFECT_MAX];
	Texture             m_BlueTex[LINE_EFFECT_MAX];
	Texture             m_UsingTex[LINE_EFFECT_MAX];
	math::Float4	    m_Color = { 2.5f,2.5f,2.5f,1 };

	math::Float2	    m_Pos[LINE_EFFECT_MAX];
	math::Float2	    m_Size[LINE_EFFECT_MAX];
	const math::Float2	m_DefinedSize{ 100.0f,100.0f };//���������̃T�C�Y
	bool	            m_Used[LINE_EFFECT_MAX];
	float	            m_Rot[LINE_EFFECT_MAX];
};

#endif //LINE_EFFECT_H_
//
////
////#include <memory>
////#include "GameCreateSystem.h"
////#include "Line.h"
////
////#define MOVECHAN_EFFECT_BALL_MAX 16 //�{�[���̕��̐�
////#define MOVECHAN_EFFECT_GROUP_TAIL_MAX 40 //�O���[�v�̐�
////#define MOVECHAN_EFFECT_TAIL_MAX 3 //�ЂƃO���[�v�Ɋ܂܂�鐔
////
//////�d�C�̐F
////typedef enum {
////	MOVECHAN_EFFECT_YELLOW,//���F 
////	MOVECHAN_EFFECT_BLUE //��
////}MOVECHAN_EFFECT_COLOR;
////
////class State;
////
/////*=========================================================================
////�@�e
////=========================================================================*/
////class MoveChanEffect
////{
////public:
////	MoveChanEffect() = delete;
////	MoveChanEffect(math::Float2& movechan) : m_MoveChanPos(movechan) {};
////	~MoveChanEffect() {}
////
////	virtual void Update() {}
////	virtual void Draw() {}
////	virtual void Set() {}
////
////
////protected:
////	Texture			m_YellowTex, m_BlueTex, m_UsingTex;
////
////	math::Float2& m_MoveChanPos = nullptr;
////	MOVECHAN_EFFECT_COLOR m_CurColor = MOVECHAN_EFFECT_BLUE;
////
////};