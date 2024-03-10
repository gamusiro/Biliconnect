/*=========================================================================
	Date : 2021/12/21(火)	Fade.cpp
		Author : がむしるぉ
		Update :
=========================================================================*/
#include "Application.h"
#include "SceneManager.h"
#include "GameCreateSystem.h"

#include "Fade.h"
#include "SEManager.h"
using namespace math;

#define FADE_RATE 0.02f

Application*		Fade::m_Application = nullptr;
FADE_MODE			Fade::m_Mode = FADE_MODE::NONE;
FADE_TYPE			Fade::m_Type = FADE_TYPE::ALPHA;
SCENE_TYPE			Fade::m_Next;
Float4				Fade::m_Color;
UINT				Fade::m_WaitFrame = 0;
UINT				Fade::m_CountFrame = 0;
Texture				Fade::m_Texture;

/*=============================================================================================
	初期化処理
=============================================================================================*/
void Fade::Init(Application* app)
{
	m_Application = app;
	m_Mode	= FADE_MODE::NONE;
	m_Next	= SCENE_TYPE::NONE;
	m_Color = Float4(1, 1, 1, 1);
}

/*=============================================================================================
	終了処理
=============================================================================================*/
void Fade::Uninit()
{
	m_Application = nullptr;
}

/*=============================================================================================
	更新処理
=============================================================================================*/
void Fade::Update()
{
	//フェード処理中であれば
	if (m_Mode != FADE_MODE::NONE)
	{
		//フェードアウトの処理
		if (m_Mode == FADE_MODE::FADE_OUT)
		{
			m_Color.w += FADE_RATE;

			if (m_Color.w >= 1.0f)
			{
				//フェードイン処理に切り替える
				m_Color.w = 1.0f;
				m_Mode = FADE_MODE::FADE_IN;

				//次のシーンに切り替える
				m_Application->GetSceneManager()->Set(m_Next);
			}
		}
		else if (m_Mode == FADE_MODE::FADE_IN)
		{
			if (m_CountFrame > m_WaitFrame)
			{
				m_Color.w -= FADE_RATE;

				if (m_Color.w <= 0.0f)
				{
					//フェードイン処理に切り替える
					m_Color.w = 0.0f;
					m_Mode = FADE_MODE::NONE;
				}
			}
			else
			{//フレームのカウント
				m_CountFrame++;
			}
		}

	}
}

/*=============================================================================================
	描画処理
=============================================================================================*/
void Fade::Draw()
{
	if (m_Mode != FADE_MODE::NONE)
	{
		switch (m_Type)
		{
		case FADE_TYPE::ALPHA	: DrawAlpha();		break;
		case FADE_TYPE::STRIPE	: DrawStripe();		break;
		case FADE_TYPE::DIAMOND	: DrawDiamond();	break;
		case FADE_TYPE::STAIR	: DrawStair();		break;
		case FADE_TYPE::MASK	: DrawTexture();	break;
		case FADE_TYPE::CHAN	: DrawChan();		break;
		default:
			break;
		}
	}
}

/*=============================================================================================
	シーンを移動するフェード処理
=============================================================================================*/
void Fade::Transition(SCENE_TYPE next, FADE_TYPE type, const Texture* texture, Float3 rgb, UINT waitFrame)
{
	m_Next			= next;
	m_Mode			= FADE_MODE::FADE_OUT;
	m_CountFrame	= 0;
	m_WaitFrame		= waitFrame;
	m_Type			= type;

	m_Texture.Reset();
	if (texture)
	{//テクスチャがnullptrでなければ
		m_Texture = *texture;
	}

	m_Color = Float4(rgb.x, rgb.y, rgb.z, 0.0f);

	if(type != FADE_TYPE::ALPHA)
	SEManager::Play(SOUND::FADE);
}

/*=============================================================================================
	フェードの状態を取得する
=============================================================================================*/
bool  Fade::GetState()
{
	if (m_Mode != FADE_MODE::NONE)
		return false;

	return true;
}

/*=============================================================================================
	フェード描画処理(アルファ)
=============================================================================================*/
void Fade::DrawAlpha()
{
	Sprite::DrawLeftTop(
		Float2(),
		Float2(SCREEN_WIDTH, SCREEN_HEIGHT),
		nullptr,
		m_Color
	);
}

/*=============================================================================================
	フェード描画処理(ストライプ)
=============================================================================================*/
void Fade::DrawStripe()
{
	const int STRIPE_NUM = 8;
	float size = SCREEN_WIDTH / STRIPE_NUM;

	for (int i = 0; i < STRIPE_NUM; i++)
	{
		Sprite::DrawLeftTop(
			Float2(0 + size * i, 0),
			Float2(size * m_Color.w, SCREEN_WIDTH),
			nullptr,
			Float4(m_Color.x, m_Color.y, m_Color.z, 1.0f));
	}
}

/*=============================================================================================
	フェード描画処理(ダイヤモンド)
=============================================================================================*/
void Fade::DrawDiamond()
{
	const int ROW_NUM	 = 10;
	const int COLUMN_NUM = 20;

	float sizeX = SCREEN_WIDTH  / COLUMN_NUM;
	float sizeY = SCREEN_HEIGHT / ROW_NUM;

	for (int y = 0; y < ROW_NUM + 1; y++)
	{
		int mod = y % 2;
		for (int x = 0; x < COLUMN_NUM + 1; x++)
		{
			Sprite::DrawMask(
				Float2(sizeX * x + (sizeX * 0.5f * mod), (sizeY * y)),
				Float2(sizeY*1.5f, sizeY*1.5f) * m_Color.w + 10.0f,
				&m_Texture,
				Float4(m_Color.x, m_Color.y, m_Color.z, 1.0f),
				 + (360.f * m_Color.w)
			);
		}
	}
}

/*=============================================================================================
	フェード描画処理(階段状)
=============================================================================================*/
void Fade::DrawStair()
{
	const int ROW_NUM = 8;
	float sizeY = SCREEN_HEIGHT / ROW_NUM;
	float sizeX[ROW_NUM] = 
	{
		1.0f, 1.1f, 1.2f, 1.3f,
		1.4f, 1.5f, 1.6f, 1.7f
	};

	for (int y = 0; y < ROW_NUM; y++)
	{
		Sprite::DrawLeftTop(
			Float2(0, sizeY * y),
			Float2(SCREEN_WIDTH * (sizeX[y] * m_Color.w), sizeY),
			nullptr,
			Float4(m_Color.x, m_Color.y, m_Color.z, 1.0f)
		);
	}
}

/*=============================================================================================
	フェード描画処理(マスクテクスチャ)
=============================================================================================*/
void Fade::DrawTexture()
{
	Sprite::DrawMask(
		Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f),
		Float2(SCREEN_WIDTH, SCREEN_HEIGHT),
		&m_Texture,
		m_Color,
		360 * m_Color.w
	);
}

/*=============================================================================================
	フェード描画処理(ぴりふわ)
=============================================================================================*/
void Fade::DrawChan()
{
	Sprite::DrawMask(
		Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f),
		Float2(m_Color.w * 2800, m_Color.w * 2800),
		&m_Texture,
		m_Color,
		360 * m_Color.w * 1.8f
	);
}
