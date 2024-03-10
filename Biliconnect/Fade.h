/*=========================================================================
	Date : 2021/12/21(火)	Fade.h
		Author : がむしるぉ
		Update :
=========================================================================*/
#ifndef FADE_H_
#define FADE_H_

#include "main.h"
#include "SceneManager.h"

//シーンのタイプ
enum class FADE_MODE
{
	NONE,
	FADE_IN,
	FADE_OUT
};

//シーンのタイプ
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
	static void Init(Application* app);	//初期化処理
	static void Uninit();				//終了処理
	static void Update();				//更新処理
	static void Draw();					//描画処理

public:
	/*
	* @ brief
	*		シーン遷移
	* @ param
	*		next		: 次のシーン名
	*		type		: フェードタイプ
	*		rgb			: フェード唐揚げ
	*		waitFrame	: フェードインするまでの待ちフレーム数
	*/
	static void Transition(
		SCENE_TYPE next,
		FADE_TYPE type,
		const Texture* texture = nullptr,
		math::Float3 rgb = math::Float3(26.0f / 255.0f, 7.0f / 255.0f, 80.0f / 255.0f),
		UINT waitFrame = 0);

	/*
	* @ brief
	*		フェードしていない状態
	* @ return
	*		true	: フェードしてない
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
