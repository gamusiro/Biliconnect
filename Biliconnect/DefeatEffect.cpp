#include "DefeatEffect.h"
#include "Stage.h"
#include <random>
#include "Line.h"
#include "Button.h"
#include <math.h>


using namespace math;

DefeatEffect::DefeatEffect()
{
	Texture yellow, blue;
	yellow.Create("Effect/ele_0001.png", 5, 2);
	blue.Create("Effect/ele_0001.png", 5, 2);

	for (int i = 0; i < GROUP; i++)
	{

		m_GroupUse[i] = false;
		for (int j = 0; j < DEBRIS; j++)
		{
			float randTex = (float)(rand() % 2);
			if (randTex == 0)
			{
				m_Tex[i][j].Create("Effect/ele_0001.png", 5, 2);
				m_Tex[i][j].SetImageID(yellow.GetTextureID());
			}
			if (randTex == 1)
			{
				m_Tex[i][j].Create("Effect/ele_02_blue.png", 5, 2);
				m_Tex[i][j].SetImageID(blue.GetTextureID());
			}

			// m_Tex[i][j].SetImageID();

		}
	}
	this->Init();
}

void DefeatEffect::Init()
{
	for (int i = 0; i < GROUP; i++)
	{
		for (int j = 0; j < DEBRIS; j++)
		{
			m_Use[i][j] = false;
			m_SecondGroupFlag[i][j] = false;
		}
	}
}

void DefeatEffect::Uninit()
{

}

void DefeatEffect::Update()
{

	for (int i = 0; i < GROUP; i++)
	{
		if (m_GroupUse[i])
		{
			for (int j = 0; j < DEBRIS; j++)
			{

				//移動
				m_Pos[i][j] += m_Vel[i][j];
				m_Vel[i][j] *= 1.0f;

				//アニメーション
				m_Tex[i][j].Update();

				//縮小
				/*if (m_Size[i][j].x > 60.0f)
					m_Size[i][j] *= (0.95f);*/

					//消滅
				m_FrameToSet[i][j]++;
				if (m_FrameToSet[i][j] > m_FrameToBeFalse[i][j])
					m_Col[i][j].w -= 0.05f;

				if (m_Col[i][j].w < 0.0f)
					m_Use[i][j] = false;



			}
		}
	}

	//フォルスにする
	for (int i = 0; i < GROUP; i++)
	{
		for (int j = 0; j < DEBRIS; j++)
		{
			if (m_Use[i][j] == true)
				break;
			else;
			{
				m_GroupUse[i] = false;

			}
		}

	}

}

void DefeatEffect::Draw()
{
	for (int i = 0; i < GROUP; i++)
	{
		if (m_GroupUse[i])
		{
			for (int j = 0; j < DEBRIS; j++)
			{
				Sprite::DrawCenter(m_Pos[i][j] - Stage::m_MoveNow, m_Size[i][j], &m_Tex[i][j], m_Col[i][j], (float)m_Degree[i][j]);
			}
		}
	}

}

void DefeatEffect::Set(math::Float2 pos)
{
	std::random_device randoms;
	std::mt19937 rando(randoms());

	for (int i = 0; i < GROUP; i++)
	{
		if (!m_GroupUse[i])
		{
			for (int j = 0; j < DEBRIS; j++)
			{

				m_Use[i][j] = true;
				m_Pos[i][j] = pos;
				int degree = rando(), spd = (rando() % 50 + 1) + 20;

				m_Vel[i][j] = math::Float2((float)cos(degree) * spd, (float)sin(degree) * spd);

				int tempSize = rando() % 3;
				if (tempSize == 0)
					m_Size[i][j] = math::Float2(RESET_SIZE, RESET_SIZE);
				if (tempSize == 1)
					m_Size[i][j] = math::Float2(RESET_SIZE * 2.0f, RESET_SIZE * 2.0f);
				if (tempSize == 2)
					m_Size[i][j] = math::Float2(RESET_SIZE * 4.0f, RESET_SIZE * 4.0f);

				m_Tex[i][j].SetCurrentTexture(rando() % 400);

				m_FrameToSet[i][j] = 0;
				m_FrameToBeFalse[i][j] = 60;

				m_Col[i][j] = math::Float4(1.0f, 1.0f, 1.0f, 1.0f);

				//回転
				m_Degree[i][j] = rando() % 360;

			}
			m_GroupUse[i] = true;
			goto end;
		}
	}
end:;
}


DefeatEffect2::DefeatEffect2()
{
	for (int i = 0; i < GROUP; i++)
	{
		m_Tex[i].Create("Effect/explosion2.png", 11, 4, 2);
		m_Pos[i] = Float2(NULL, NULL);
		m_Size[i] = Float2(1100.0f, 1100.0f);
		m_Col[i] = { 1.2f,1.2f,1.2f,1.0f };
		isUsing[i] = false;
		m_FrameSinceToSet[i] = 0;
		m_Rot[i] = rand() % 359;
	}
}

void DefeatEffect2::Update()
{
	for (int i = 0; i < GROUP; i++)
	{
		if (isUsing[i])
		{
			m_Tex[i].Update();

			m_FrameSinceToSet[i]++;
			if (m_FrameSinceToSet[i] > 41 * 2)
				isUsing[i] = false;
		}
	}
}

void DefeatEffect2::Draw()
{
	for (int i = 0; i < GROUP; i++)
	{
		if (isUsing[i])
		{
			Sprite::DrawCenter(m_Pos[i] - Stage::m_MoveNow, m_Size[i], &m_Tex[i], m_Col[i], m_Rot[i]);
		}

	}
}

void DefeatEffect2::Set(math::Float2 pos)
{
	for (int i = 0; i < GROUP; i++)
	{
		if (!isUsing[i])
		{
			m_Pos[i] = pos;
			isUsing[i] = true;
			m_FrameSinceToSet[i] = 0;
			m_Tex[i].SetCurrentTexture(0);
			m_Tex[i].Update();
			break;
		}
	}
}


DefeatEffect3::DefeatEffect3()
{
	this->Init();
}

DefeatEffect3::~DefeatEffect3()
{
}


void DefeatEffect3::Init()
{
	m_Tex.Create("result_bg.png", 1, 1);
	m_Pos = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f };
	m_Color = math::Float4(0.0f, 0.0f, 0.0f, 0.0f);
	m_Frame = 60;
}

void DefeatEffect3::Uninit()
{
}
void DefeatEffect3::Update()
{
	m_Frame++;

	//敵にヒットすると暗くなる
	if (m_Frame <= 60)
	{
		m_Color.w += 0.1f;
		if (m_Color.w > m_AlphaMax)
			m_Color.w = m_AlphaMax;
	}
	if (m_Frame > 60)
	{
		m_Color.w -= 0.04f;
		if (m_Color.w < 0.0f)
			m_Color.w = 0.0f;
	}
}

void DefeatEffect3::Draw()
{
	Sprite::DrawCenter(m_Pos, m_Size, &m_Tex, m_Color);
}

void DefeatEffect3::Set()
{
	m_Frame = 0;
}












CharacterEffect::CharacterEffect()
{
	//this->Init();
}

CharacterEffect::~CharacterEffect()
{
}





void CharacterEffect::Init()
{
	//m_Tex[GOOD_1].Create("Effect/good2.png", 1, 1);
	//m_Tex[GOOD_2].Create("Effect/good1.png", 1, 1);
	//m_Tex[EXCELLENT_1].Create("Effect/excellent2.png", 1, 1);
	//m_Tex[EXCELLENT_2].Create("Effect/excellent1.png", 1, 1);
	//m_Tex[AMAZING_1].Create("Effect/amazing2.png", 1, 1);
	//m_Tex[AMAZING_2].Create("Effect/amazing1.png", 1, 1);
	//
	//for (int i = 0; i < MAX; i++)
	//{
	//	m_Pos[i] = { -SCREEN_WIDTH + 350.0f,SCREEN_HEIGHT * 0.5f + 350.0f };
	//	m_Vel[i] = { 400.0f,0.0f };
	//	m_Size[i] = { SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.3f };
	//	m_Color[i] = math::Float4(1.3f, 1.3f, 1.3f, 1.0f);
	//	m_Use[i] = false;
	//}

}

void CharacterEffect::Uninit()
{
}
void CharacterEffect::Update()
{
	//m_Pos[GOOD_2] = m_Pos[GOOD_1];
	//m_Pos[EXCELLENT_2] = m_Pos[EXCELLENT_1];
	//m_Pos[AMAZING_2] = m_Pos[AMAZING_1];
	//m_Use[GOOD_2] = m_Use[GOOD_1];
	//m_Use[EXCELLENT_2] = m_Use[EXCELLENT_1];
	//m_Use[AMAZING_2] = m_Use[AMAZING_1];


	////連鎖無し
	//if (AppearingCharacter == NONE)
	//{
	//	m_Color[GOOD_1].w -= 0.1f;
	//	m_Color[EXCELLENT_1].w -= 0.1f;
	//	m_Color[AMAZING_1].w -= 0.1f;
	//	m_Color[GOOD_2].w -= 0.1f;
	//	m_Color[EXCELLENT_2].w -= 0.1f;
	//	m_Color[AMAZING_2].w -= 0.1f;
	//}


	////時間が経つと連鎖が消える。
	//for (int i = 0; i < MAX; i++)
	//{
	//	if (m_Use[i])
	//	{
	//		m_Frame[i]++;
	//		if (m_Frame[i] > 60)
	//		{
	//			m_Color[i].w -= 0.1f;

	//			if(m_Color[i].w<0.0f)
	//			m_Use[i] = false;	
	//		}
	//	}

	//
	//}

	//for (int i = 0; i < MAX; i+=2)
	//{
	//}
}

void CharacterEffect::Draw()
{
	/*for (int i = 0; i < MAX; i++)
	{
		if ( i % 2 == 0)
		{
			Sprite::DrawCenter(m_Pos[i] - Stage::m_MoveNow, m_Size[i], &m_Tex[i], m_Color[i]);
		}
		if (i % 2 == 1)
		{
			float tempBlinking = sin(m_Frame[i] * 1.0f) * 0.2f+1.2f;
			Sprite::DrawCenter(m_Pos[i] - Stage::m_MoveNow, m_Size[i], &m_Tex[i], 
				Float4(tempBlinking, tempBlinking, tempBlinking, m_Color[i].w));
		}
	}*/
}

void CharacterEffect::Set(math::Float2 pos)
{	
	/*static int tempDegree = PI * (1.0f / 4.0f);
	static int tempDegree2 = PI * (1.0f / 2.0f);

	int tempCnt = 0;
	for (int i = 0; i < MAX; i++)
	{

	
		if (!m_Use[i])
		{
			tempDegree += tempDegree2;
			m_Pos[i] = { pos.x+cosf(tempDegree)*200.0f,pos.y + sinf(tempDegree) * 200.0f };
			m_Vel[i] = { 400.0f,0.0f };
			m_Color[i] = math::Float4(1.3f, 1.3f, 1.3f, 1.0f);
			m_Use[i] = true;

			m_Frame[i] = 0;
			tempCnt++;
			if(tempCnt==2)
			break;
		}
	}*/
}
