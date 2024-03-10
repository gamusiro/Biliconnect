/*=========================================================================
	Date : 2021/03/22(火)	MoveChanEffect.h
		Author : 
		Update :
=========================================================================*/
#ifndef MOVECHAN_EFFECT_H_
#define MOVECHAN_EFFECT_H_

#include "GameCreateSystem.h"

class State;
class MoveChan;

/*=========================================================================
　親
=========================================================================*/
class MoveChanEffect
{
public:
	MoveChanEffect() = delete;
	MoveChanEffect(math::Float2& movechan) : m_MoveChanPos(movechan) {};
	~MoveChanEffect(){}

	virtual void Update()	= 0;
	virtual void Draw()		= 0;

protected:
	virtual void Set() = 0;

protected:
	//電気の速さ
	typedef enum {
		MOVECHAN_EFFECT_NORMAL,//黄色 
		MOVECHAN_EFFECT_FAST //青
	}MOVECHAN_EFFECT_SPEED;

	Texture					m_YellowTex, m_BlueTex, m_UsingTex;
	math::Float2&			m_MoveChanPos;
	MOVECHAN_EFFECT_SPEED	m_CurSpeed = MOVECHAN_EFFECT_FAST;
	math::Float4			m_Color = { 1.4f, 1.4f, 1.4f, 1 };

};
/*=========================================================================
　ボール
=========================================================================*/
class MoveChanEffectBall :public MoveChanEffect
{
public:
	MoveChanEffectBall(math::Float2& movechan);
	~MoveChanEffectBall();

	void Update() override;
	void Draw()override;
	void Set()override {}

protected:
	constexpr static float FADE_SPEED = 0.05f;	//フェードの速さ
protected:
//#define MOVECHAN_EFFECT_BALL_MAX 16 //ボールの方の数

	math::Float2	m_Size = { 400,400 };
	math::Float4	m_YellowColor = { 1.2f,1.2f,1.2f,1 };
	math::Float4	m_BlueColor = { 1.1f,1.1f,1.1f,1 };

private:
	Texture               m_BGTex;
};

/*=========================================================================
　サークル
=========================================================================*/
class MoveChanEffectCircle :public MoveChanEffectBall
{
public:
	MoveChanEffectCircle() = delete;
	MoveChanEffectCircle(math::Float2& movechan);

	void Draw() override;

private:
	math::Float2	m_Size = { 250,250 };
};

/*=========================================================================
　スパーク
=========================================================================*/
class MoveChanEffectSpark :public MoveChanEffect
{
public:
	MoveChanEffectSpark() = delete;
	MoveChanEffectSpark(math::Float2& movechan);

	void Update() override;
	void Draw()override;
	void Set()override;

private:
	constexpr const static int SPARK_MAX = 20; //スパークの数

private:
	int                 m_Frame = 0;//フレーム
	const int           m_frameToSetMoveChanEffect = 160;//何フレームごとにセットするか
	const int           m_AnimationSpeed = 5;//アニメーションの速さ
	Texture             m_YellowTex[SPARK_MAX];
	Texture             m_BlueTex[SPARK_MAX];
	Texture             m_PinkTex[SPARK_MAX];
	Texture             m_UsingTex[SPARK_MAX];
	int                 m_FrameToDelete[SPARK_MAX] = {};//現れてから消えるまでのフレーム

	math::Float2	    m_Pos[SPARK_MAX];
	math::Float2	    m_RandomPos[SPARK_MAX];
	math::Float2	    m_Size[SPARK_MAX];
	const math::Float2	m_DefinedSize{ 50.0f,50.0f };//初期化時のサイズ
	bool	            m_Used[SPARK_MAX];
	float	            m_Rot[SPARK_MAX] = {};
};

/*=========================================================================
　しっぽ
=========================================================================*/
class MoveChanEffectTail :public MoveChanEffect
{
public:
	MoveChanEffectTail() = delete;
	MoveChanEffectTail(math::Float2& movechan);
	~MoveChanEffectTail();

	void Update() override;
	void Draw()override;
	void Set()override;


private:
	constexpr const static int TAIL_GROUP_MAX	= 80; //グループの数
	constexpr const static int TAIL_MAX			= 3;  //ひとグループに含まれる数

private:
	int                 m_Frame = 0;//フレーム
	const int           m_frameToSetMoveChanEffectFast = 1;//何フレームごとにセットするか(NORMAL)
	const int           m_frameToSetMoveChanEffectNormal = 3;//何フレームごとにセットするか(FAST)
	const int           m_AnimationSpeed = 2;//アニメーションの速さ
	Texture             m_YellowTex[TAIL_GROUP_MAX][TAIL_MAX];
	Texture             m_BlueTex[TAIL_GROUP_MAX][TAIL_MAX];
	Texture             m_PinkTex[TAIL_GROUP_MAX][TAIL_MAX];
	Texture             m_UsingTex[TAIL_GROUP_MAX][TAIL_MAX];

	math::Float2	    m_Pos[TAIL_GROUP_MAX][TAIL_MAX];
	math::Float2	    m_Size[TAIL_GROUP_MAX][TAIL_MAX];
	const math::Float2	m_DefinedSize{ 200.0f,200.0f };//初期化時のサイズ
	const math::Float2	m_ReducedSize{ 4.2f,4.2f };//小さくなる速さ
	bool	            m_Used[TAIL_GROUP_MAX][TAIL_MAX];
	float	            m_Rot[TAIL_GROUP_MAX][TAIL_MAX] = {};

};

/*=========================================================================
  BG
=========================================================================*/
class MoveChanEffectBG :public MoveChanEffect
{
public:
	MoveChanEffectBG(math::Float2& movechan);
	~MoveChanEffectBG();
	void Update() override;
	void Draw()override;
	void SetSpd(MOVECHAN_EFFECT_SPEED ms);

private:
	Texture             m_Tex;
	math::Float4	    m_Color = { 0.0f,0.0f,0.0f,1.0f };
	math::Float2	    m_Pos = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f };
	math::Float2	    m_Size = { SCREEN_WIDTH,SCREEN_HEIGHT};
	const float         m_AlphaMax = 0.4f;
	MOVECHAN_EFFECT_SPEED m_MoveChanSpd;
};

#endif//MOVECHAN_EFFECT_H_
