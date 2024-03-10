#include "Score.h"
#include "SaveStage.h"
#include "EnemyNum.h"
#include "Game.h"
#include "Stage.h"
#include "Coin.h"

using namespace math;

int Score::m_Score(0);
int Score::m_NowScore(0);
int Score::trigger(false);
int Score::timer(0);


Score::Score() : m_Size(Float2(70, 70)), m_digit(2)
{
	Texture num;

	num.Create("num.png", 10, 1);
	for (int i = 0; i < SCORE_EFFECT_MAX; i++) 
	{
		m_EffectTex[i].Create("Effect/ele_02.png", 5, 2);
	}
	Numerator.Create(nullptr, 10, 1);
	Numerator.SetImageID(num.GetTextureID());
	Denominator.Create(nullptr, 10, 1);
	Denominator.SetImageID(num.GetTextureID());
	Slash.Create("sl.png", 1, 1);
	Waku.Create("suuji_waku.png", 1, 1);
	WakuL.Create("suuji_waku.png", 1, 1);
	WakuL.SetTextureDirection(DIRECTION_TEXTURE::RIGHT);

	m_ColorF = { 1.2f,1.2f,1.2f,1.0f };
	m_ColorC[0] = { 0.3f,0.3f,0.3f,1.0f };
	m_ColorC[1] = { 0.3f,0.3f,0.3f,1.0f };

	timer = 0;
	trigger = false;

	//スコアエフェクト
	for (int i = 0; i < SCORE_EFFECT_MAX; i++)
	{
		m_SE[i].use = false;
	}

	int stagenum = StageNum::Get() % 10;

	// ファイル
	Folder.Create("File/file_icon.png", 1, 1);

	if (stagenum == 0)
		File.Create("File/book_file_icon.png", 1, 1);
	else if (stagenum == 1)
		File.Create("File/cloud_file_icon.png", 1, 1);
	else if (stagenum == 2)
		File.Create("File/document_file_icon.png", 1, 1);
	else if (stagenum == 3)
		File.Create("File/download_file_icon.png", 1, 1);
	else if (stagenum == 4)
		File.Create("File/game_file_icon.png", 1, 1);
	else if (stagenum == 5)
		File.Create("File/movie_file_icon.png", 1, 1);
	else if (stagenum == 6)
		File.Create("File/music_file_icon.png", 1, 1);
	else if (stagenum == 7)
		File.Create("File/picture_file_icon.png", 1, 1);
	else if (stagenum == 8)
		File.Create("File/screen_file_icon.png", 1, 1);
	else if (stagenum == 9)
		File.Create("File/zip_file_icon.png", 1, 1);
}

void Score::Update()
{
	if(Coin::Get() == 1)
		m_ColorC[1] = { 1.f,1.0f,1.0f,1.0f };
	if (Coin::Get() == 2)
		m_ColorC[0] = { 1.f,1.0f,1.0f,1.0f };
	if (Coin::Get() == 3)
	{
		m_ColorC[0] = { 1.f,1.0f,1.0f,1.0f };
		m_ColorC[1] = { 1.f,1.0f,1.0f,1.0f };
	}

	for (int i = 0; i < SCORE_EFFECT_MAX; i++)
	{
		m_EffectTex[i].Update();
	}

	if (EnemyNum::GetKill() >= 10)m_digit = 2;
	else if (EnemyNum::GetKill() >= 0)m_digit = 1;

	m_ColorF = { 1,1,1,0.7f };

	if (trigger)
	{
		SetEffect();
	
		timer++;

		if (timer > 100)
		{
			timer = 0;
			trigger = false;
		}
	}
	


		//スコアエフェクト
		for (int i = 0; i < SCORE_EFFECT_MAX; i++)
		{
			if (m_SE[i].use && Game::GetGameState() != 1)
			{
				//縮小
				m_SE[i].size.x -= 1.2f;
				m_SE[i].size.y -= 1.2f;

				//移動処理
				m_SE[i].vel += m_SE[i].addvel;
				m_SE[i].vel.x *= 1.0f;
				m_SE[i].vel.y *= 0.5f;

				//色を薄くする
				m_SE[i].color.w -= 0.065f;

				//回転
				m_SE[i].rot += 0.03f;

				//useのfalse処理
				if (m_SE[i].color.w < 0.0f)
				{
					m_SE[i].use = false;
				}
			}
	}

		if (trigger)
		{
			m_Frame++;
			Blinking = sin(m_Frame * 0.8f) * 0.2f + 1.2f;
		}
		else
		{
			Blinking = 1.0f;
		}

}

void Score::Draw()
{
	// 分母
	int number = EnemyNum::Get();

	Sprite::DrawCenter(Float2(1720, 80), Float2(620, 260), &Waku, { 1,1,1,0.7f });
	Sprite::DrawCenter(Float2(-70, 80), Float2(620, 260), &WakuL, { 1,1,1,0.7f });
	Sprite::DrawCenter(Float2(1730 + PLUS_X, 400 + PLUS_Y), Float2(370, 300), &Waku, m_ColorF);

	Sprite::DrawCenter(Float2(90, 75), Float2(140, 140), &File, m_ColorC[0]);
	Sprite::DrawCenter(Float2(90, 80), Float2(140, 140), &Folder, m_ColorC[1]);

	/*Sprite::DrawCenter(Float2(-70, 80), Float2(140, 140), &File, { 1,1,1,0.7f });
	Sprite::DrawCenter(Float2(-70, 80), Float2(140, 140), &Folder, { 1,1,1,0.7f });*/


	for (int i = 0; i < SCORE_EFFECT_MAX; i++)
	{
		if (m_SE[i].use)
			Sprite::DrawCenter(m_SE[i].pos + m_SE[i].vel, m_SE[i].size, &m_EffectTex[i], m_SE[i].color, m_SE[i].rot);
	}


	for (int i = 0; i < 2; i++)
	{
		float x = (float)(number % 10);

		float px = 1810 + DISTANCE_X * i;
		float py = 400;
		float pw = m_Size.x;
		float ph = m_Size.y;

		float tw = 1.0f / 10;
		float th = 1.0f / 1;
		float tx = x * tw;
		float ty = 0.0f;

		Numerator.SetStartUVPosition(Float2(tx, ty));

		Sprite::DrawLeftTop(Float2(px + PLUS_X, py + PLUS_Y), Float2(pw, ph), &Numerator, Float4(Blinking, Blinking, Blinking, 1.0f));

		// 次の桁へ
		number /= 10;
	}
	// 分子
	int number2 = EnemyNum::GetKill();

	for (int i = 0; i < m_digit; i++)
	{
		float x = (float)(number2 % 10);

		float px = 1650 + DISTANCE_X * i;
		float py = 300;
		float pw = m_Size.x;
		float ph = m_Size.y;

		float tw = 1.0f / 10;
		float th = 1.0f / 1;
		float tx = x * tw;
		float ty = 0.0f;

		Denominator.SetStartUVPosition(Float2(tx, ty));

		Sprite::DrawLeftTop(Float2(px + PLUS_X, py + PLUS_Y), Float2(pw, ph), &Denominator, Float4(Blinking, Blinking, Blinking, 1.0f));

		// 次の桁へ
		number2 /= 10;
	}

	Sprite::DrawLeftTop(Float2(1655 + PLUS_X, 310 + PLUS_Y), Float2(160, 160), &Slash, Float4(Blinking, Blinking, Blinking, 1.0f));

}

void Score::SetEffect()
{
	for (int i = 0; i < SCORE_EFFECT_MAX; i++)
	{
		if (!m_SE[i].use)
		{
			m_SE[i].use = true;
			m_SE[i].pos = Float2(1650+ rand()%200-100, 250+rand()%200-100);
			m_SE[i].vel = Float2(0, 0);
			m_SE[i].size = Float2(100 * 1.5, 100 * 2.0);
			m_SE[i].rot = rand() % 360;
			m_SE[i].color = { 1.5f,1.5f,1.5f,1.0f };

			////////////////////////////////	乱数によって飛ばす方向を決定する	////////////////////////////////////
			int dirX, dirY;
			if (rand() % 2 == 0)
				dirX = 0;
			else
				dirX = 1;
			if (rand() % 2 == 0)
				dirY = 0;
			else
				dirY = 1;

			//飛ばす早さ
			float spd = 1.5f;

			if (dirX == 0 && dirY == 0)
				m_SE[i].addvel = Float2((float)(rand() % 10 + 7) * spd, (float)(rand() % 10 + 3) * spd);

			if (dirX == 1 && dirY == 1)
				m_SE[i].addvel = Float2((float)(rand() % 10 + 7) * spd, (float)(rand() % 10 + 3) * spd);

			if (dirX == 0 && dirY == 1)
				m_SE[i].addvel = Float2((float)(rand() % 10 + 7) * spd, (float)(rand() % 10 + 3) * spd);

			if (dirX == 1 && dirY == 0)
				m_SE[i].addvel = Float2((float)(rand() % 10 + 7) * spd, (float)(rand() % 10 + 3) * spd);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////

			break;
		}
	}
}
