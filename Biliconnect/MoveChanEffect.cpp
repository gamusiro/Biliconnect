/*=========================================================================
	Date : 2021/03/22(火)	MoveChanEffect.h
		Author :
		Update :
=========================================================================*/
#include "MoveChanEffect.h"
#include "Line.h"
#include "Stage.h"
#include <random>
#include "MoveChan.h"

using namespace math;

/*=========================================================================
 ボール
=========================================================================*/
MoveChanEffectBall::MoveChanEffectBall(math::Float2& movechan) :MoveChanEffect(movechan)
{
	m_YellowTex.Create("Effect/ball_yellow.png", 5, 5);
	m_BlueTex.Create("Effect/ball_blue.png", 5, 5);
	m_UsingTex		= m_YellowTex;//こっちをいじくる
	m_MoveChanPos	= movechan;
	m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
}

MoveChanEffectBall::~MoveChanEffectBall()
{
	m_MoveChanPos;
}

void MoveChanEffectBall::Update()
{
	int num = StageNum::Get() % 5;

	if (StageEnd::Get() && num == 4)
	{
		/// //////////////////////////////////////////テストプレイ用
		if (Dash::Get())
			m_CurSpeed = MOVECHAN_EFFECT_FAST;
		else
			m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
		///////////////////////////////////////////////////////////
	}
	else if (StageEnd::Get())
	{
		m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
	}
	else if (!StageEnd::Get() && !StageStart::Get())
	{
		/// //////////////////////////////////////////テストプレイ用
		if (Dash::Get())
			m_CurSpeed = MOVECHAN_EFFECT_FAST;
		else
			m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
		///////////////////////////////////////////////////////////
	}

	

	//アニメーションの更新
	m_UsingTex.Update();
	m_BlueTex.Update();
	m_YellowTex.Update();


	float speedToFadeAd = 0.2f;//フェードの速さ
	float speedToFadeDe = 0.05f;//フェードの速さ
	if (m_CurSpeed == MOVECHAN_EFFECT_NORMAL)
	{
		m_BlueColor.w -= speedToFadeDe;
		if (m_BlueColor.w < 0.0f)
			m_BlueColor.w = 0.0f;
	}
	if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
	{
		m_BlueColor.w += speedToFadeAd;
		if (m_BlueColor.w > 1.5f)
			m_BlueColor.w = 1.5f;
	}
	//大きさの変更
	if (m_CurSpeed == MOVECHAN_EFFECT_NORMAL)
	{
		//縮小
		if (m_Size.x > 200.0f)
		{
			m_Size.x -= 10.0f;
			m_Size.y -= 10.0f;

			if (m_Size.x < 200.0f)
			{
				m_Size.x = 200.0f;
				m_Size.y = 200.0f;
			}
		}
	}

	if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
	{
		//拡大
		if (m_Size.x < 600.0f)
		{
			m_Size.x += 80.0f;
			m_Size.y += 80.0f;

			if (m_Size.x > 600.0f)
			{
				m_Size.x = 600.0f;
				m_Size.y = 600.0f;
			}
		}
	}
}

void MoveChanEffectBall::Draw()
{
	if (!m_CurSpeed == MOVECHAN_EFFECT_FAST)
		Sprite::DrawCenter(m_MoveChanPos - Stage::m_MoveNow, m_Size, &m_YellowTex, m_YellowColor);
	else 
		Sprite::DrawCenter(m_MoveChanPos - Stage::m_MoveNow, m_Size - m_Color.w * 80.0f, &m_YellowTex, m_YellowColor);

	Sprite::DrawCenter(m_MoveChanPos - Stage::m_MoveNow, m_Size, &m_BlueTex, m_BlueColor);
	
}

/*=========================================================================
 サークル
=========================================================================*/
MoveChanEffectCircle::MoveChanEffectCircle(math::Float2& movechan) :MoveChanEffectBall(movechan)
{
	m_BlueTex.Create("Effect/circle_pink.png", 5, 5);
	m_YellowTex.Create("Effect/circle_blue.png", 5, 5);
	m_UsingTex = m_YellowTex;
	m_MoveChanPos = movechan;
}

void MoveChanEffectCircle::Draw()
{
}

/*=========================================================================
 スパーク
=========================================================================*/
MoveChanEffectSpark::MoveChanEffectSpark(math::Float2& movechan) :MoveChanEffect(movechan)
{
	std::random_device randoms;
	std::mt19937 rando(randoms());

	for (int i = 0; i < SPARK_MAX; i++)
	{
		m_YellowTex[i].Create("Effect/tail_yellow.png", 3, 3, m_AnimationSpeed);
		m_BlueTex[i].Create("Effect/tail_blue.png", 3, 3, m_AnimationSpeed);
		m_PinkTex[i].Create("Effect/tail_pink.png", 3, 3, m_AnimationSpeed);
		m_UsingTex[i] = m_BlueTex[i];
		m_Size[i] = m_DefinedSize;
		m_Rot[i] = (static_cast<float>(rando() % 40)) * 0.1f;
	
		m_Used[i] = false;
	}
}

void MoveChanEffectSpark::Update()
{
	if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
	{
		//■スパークのセット
		if ((rand() % 2) == 0)
			this->Set();
		m_Frame++;
	}

	for (int i = 0; i < SPARK_MAX; i++)
	{
		if (m_Used[i])
		{
			//アニメーションの更新
			m_UsingTex[i].Update();
			m_BlueTex[i].Update();
			m_YellowTex[i].Update();
			m_PinkTex[i].Update();

			//消滅処理
			m_FrameToDelete[i]++;
			if (m_FrameToDelete[i] >=  m_AnimationSpeed * 3)
				m_Used[i] = false;
		
		}
	}
}

void MoveChanEffectSpark::Draw()
{

}

void MoveChanEffectSpark::Set()
{
	std::random_device randoms;
	std::mt19937 rando(randoms());

	for (int i = 0; i < SPARK_MAX; i++)
	{
		if (!m_Used[i])
		{
			m_Pos[i] = Float2(m_MoveChanPos.x + m_RandomPos[i].x - 300, m_MoveChanPos.y + m_RandomPos[i].y - 300);
			m_FrameToDelete[i] = 0;
			m_RandomPos[i] = Float2(static_cast<float>(rando() % 600), static_cast<float>(rando() % 600));
			m_Used[i] = true;
			break;
		}
		
	}
}


/*=========================================================================
 しっぽ
=========================================================================*/
MoveChanEffectTail::MoveChanEffectTail(math::Float2& movechan) :MoveChanEffect(movechan)
{
	for (int i = 0; i < TAIL_GROUP_MAX; i++)
	{
		for (int j = 0; j < TAIL_MAX; j++)
		{
			m_YellowTex[i][j].Create("Effect/ele_02.png", 5, 2, m_AnimationSpeed);
			m_BlueTex[i][j].Create("Effect/ele_02_blue.png", 5, 2, m_AnimationSpeed);
			m_PinkTex[i][j].Create("Effect/ele_02.png", 5, 2, m_AnimationSpeed);
			m_UsingTex[i][j] = m_YellowTex[i][j];
			m_Used[i][j] = false;
		}
	}
}

MoveChanEffectTail::~MoveChanEffectTail()
{
}

void MoveChanEffectTail::Update()
{
	int num = StageNum::Get() % 5;

	if (StageEnd::Get() && num == 4)
	{
		/// //////////////////////////////////////////テストプレイ用
		if (Dash::Get())
			m_CurSpeed = MOVECHAN_EFFECT_FAST;
		else
			m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
		///////////////////////////////////////////////////////////
	}
	else if (StageEnd::Get())
	{
		m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
	}
	else if (!StageEnd::Get() && !StageStart::Get())
	{
		/// //////////////////////////////////////////テストプレイ用
		if (Dash::Get())
			m_CurSpeed = MOVECHAN_EFFECT_FAST;
		else
			m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
		///////////////////////////////////////////////////////////
	}
	else
		m_CurSpeed = MOVECHAN_EFFECT_NORMAL;


	//■しっぽのセット
	if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
	{
		if (m_Frame % m_frameToSetMoveChanEffectFast == 0)
			this->Set();
		m_Frame++;
	}

	if (m_CurSpeed == MOVECHAN_EFFECT_NORMAL)
	{
		if (m_Frame % m_frameToSetMoveChanEffectNormal == 0)
			this->Set();
		m_Frame++;
	}

	for (int i = 0; i < TAIL_GROUP_MAX; i++)
	{
		for (int j = 0; j < TAIL_MAX; j++)
		{
			if (m_Used[i][j])
			{
				//■セット後の処理
				//アニメ-ションの更新処理
				m_UsingTex[i][j].Update();

				//サイズの変更
				m_Size[i][j] -= m_ReducedSize;

				//削除処理
				if (m_Size[i][j].x < 0.0f)
					m_Used[i][j] = false;
			}
		}
	}
}

void MoveChanEffectTail::Draw()
{
	for (int i = 0; i < TAIL_GROUP_MAX; i++)
	{
		for (int j = 0; j < TAIL_MAX; j++)
		{
			if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
			{
				if (m_Used[i][j])
				{
					Sprite::DrawCenterK(m_Pos[i][j] - Stage::m_MoveNow, m_Size[i][j], &m_UsingTex[i][j], m_Color, m_Rot[i][j]);
				}
			}
			if (m_CurSpeed == MOVECHAN_EFFECT_NORMAL)
			{
				if (j < 2)
				 {
					Sprite::DrawCenterK(m_Pos[i][j] - Stage::m_MoveNow, m_Size[i][j], &m_UsingTex[i][j], m_Color, m_Rot[i][j]);
				}
			}
		}
	}
}

void MoveChanEffectTail::Set()
{
	std::random_device randoms;
	std::mt19937 rando(randoms());

	for (int i = 0; i < TAIL_GROUP_MAX; i++)
	{
		if (!m_Used[i][0])
		{
			for (int j = 0; j < TAIL_MAX; j++)
			{
				if (rando() % 5 == 0)
				{
					m_UsingTex[i][j] = m_BlueTex[i][j];
					m_Size[i][j] = m_DefinedSize;
					m_Size[i][j] *= 1.25f;
				}
				else 
				{
					m_UsingTex[i][j] = m_YellowTex[i][j];
					m_Size[i][j] = m_DefinedSize;
					m_Size[i][j].y *= 1.0f;
				}
				

			

				if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
				{
					if (rando() % 5 == 0)
						m_UsingTex[i][j] = m_PinkTex[i][j];
					else
						m_UsingTex[i][j] = m_BlueTex[i][j];

					m_Size[i][j] = m_DefinedSize;
					m_Size[i][j] *= 2.0f;
				}

				m_Pos[i][j]		= Float2(m_MoveChanPos.x + static_cast<float>(rando() % 100) - 50, m_MoveChanPos.y + static_cast<float>(rando() % 100) - 50);
				
				m_Rot[i][j]		= (static_cast<float>(rando() % 40)) * 0.1f;
				m_Used[i][j]	= true;

				m_UsingTex[i][j].SetCurrentTexture(rando() % 10);
			}
			break;
		}
	}
}

/*=========================================================================
 BG
=========================================================================*/
MoveChanEffectBG::MoveChanEffectBG(math::Float2&  movechan) : MoveChanEffect(movechan)
{
	m_Tex.Create("result_bg.png",1,1);
	m_Color = { 0.0f,0.0f,0.0f,m_AlphaMax };
}

MoveChanEffectBG::~MoveChanEffectBG()
{
}

void MoveChanEffectBG::Update()
{
	//スピードが上がると暗くなる
	if (m_MoveChanSpd == MOVECHAN_EFFECT_FAST)
	{
		m_Color.w += 0.01f;
		if (m_Color.w > m_AlphaMax)
			m_Color.w = m_AlphaMax;
	}
	if (m_MoveChanSpd == MOVECHAN_EFFECT_NORMAL)
	{
		m_Color.w -= 0.01f;
		if (m_Color.w < 0.0f)
			m_Color.w = 0.0f;
	}

}

void MoveChanEffectBG::Draw()
{
	Sprite::DrawCenter(m_Pos, m_Size, &m_Tex, m_Color);
}

void MoveChanEffectBG::SetSpd(MOVECHAN_EFFECT_SPEED ms)
{
	m_MoveChanSpd = ms;
}


//////////////////////////
///*=========================================================================
//	Date : 2021/03/22(火)	MoveChanEffect.h
//		Author :
//		Update :
//=========================================================================*/
//#include "MoveChanEffect.h"
//#include "Line.h"
//#include "Stage.h"
//#include <random>
//#include "MoveChan.h"
//
//using namespace math;
//
///*=========================================================================
// ボール
//=========================================================================*/
//MoveChanEffectBall::MoveChanEffectBall(math::Float2& movechan) :MoveChanEffect(movechan)
//{
//	m_YellowTex.Create("fx_hit_test.png", 7, 1, 2);
//	m_BlueTex.Create("fx_hit_test.png", 7, 1, 2);
//	m_UsingTex = m_YellowTex;//こっちをいじくる
//	m_MoveChanPos = movechan;
//	m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
//}
//
//MoveChanEffectBall::~MoveChanEffectBall()
//{
//	m_MoveChanPos;
//}
//
//void MoveChanEffectBall::Update()
//{
//
//
//
//	int num = StageNum::Get() % 5;
//
//	if (StageEnd::Get() && num == 4)
//	{
//		/// //////////////////////////////////////////テストプレイ用
//		if (Dash::Get() ||
//			(Controller::GetButtonPressRShoulder() || Input::KeyboardPress(DIK_RIGHT)) && !Dash::Get() ||
//			(Controller::GetButtonPressLShoulder() || Input::KeyboardPress(DIK_LEFT)) && !Dash::Get())
//			m_CurSpeed = MOVECHAN_EFFECT_FAST;
//		else
//			m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
//		///////////////////////////////////////////////////////////
//	}
//	else if (StageEnd::Get())
//	{
//		m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
//	}
//	else if (!StageEnd::Get() && !StageStart::Get())
//	{
//		/// //////////////////////////////////////////テストプレイ用
//		if (Dash::Get() ||
//			(Controller::GetButtonPressRShoulder() || Input::KeyboardPress(DIK_RIGHT)) && !Dash::Get() ||
//			(Controller::GetButtonPressLShoulder() || Input::KeyboardPress(DIK_LEFT)) && !Dash::Get())
//			m_CurSpeed = MOVECHAN_EFFECT_FAST;
//		else
//			m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
//		///////////////////////////////////////////////////////////
//	}
//
//
//
//	//アニメーションの更新
//	m_UsingTex.Update();
//	m_BlueTex.Update();
//	m_YellowTex.Update();
//
//
//	float speedToFadeAd = 0.2f;//フェードの速さ
//	float speedToFadeDe = 0.05f;//フェードの速さ
//	if (m_CurSpeed == MOVECHAN_EFFECT_NORMAL)
//	{
//		m_BlueColor.w -= speedToFadeDe;
//		if (m_BlueColor.w < 0.0f)
//			m_BlueColor.w = 0.0f;
//	}
//	if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
//	{
//		m_BlueColor.w += speedToFadeAd;
//		if (m_BlueColor.w > 1.5f)
//			m_BlueColor.w = 1.5f;
//	}
//	//大きさの変更
//	if (m_CurSpeed == MOVECHAN_EFFECT_NORMAL)
//	{
//		//縮小
//		if (m_Size.x > 300.0f)
//		{
//			m_Size.x -= 6.0f;
//			m_Size.y -= 6.0f;
//
//			if (m_Size.x < 300.0f)
//			{
//				m_Size.x = 200.0f;
//				m_Size.y = 200.0f;
//			}
//		}
//	}
//
//	if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
//	{
//		//拡大
//		if (m_Size.x < 400.0f)
//		{
//			m_Size.x += 50.0f;
//			m_Size.y += 50.0f;
//
//			if (m_Size.x > 400.0f)
//			{
//				m_Size.x = 400.0f;
//				m_Size.y = 400.0f;
//			}
//		}
//	}
//}
//
//void MoveChanEffectBall::Draw()
//{
//	if (!m_CurSpeed == MOVECHAN_EFFECT_FAST)
//		Sprite::DrawCenter(m_MoveChanPos - Stage::m_MoveNow, m_Size, &m_YellowTex, m_YellowColor);
//	else
//		Sprite::DrawCenter(m_MoveChanPos - Stage::m_MoveNow, m_Size - m_Color.w * 80.0f, &m_YellowTex, m_YellowColor);
//
//	Sprite::DrawCenter(m_MoveChanPos - Stage::m_MoveNow, m_Size, &m_BlueTex, m_BlueColor);
//
//}
//
///*=========================================================================
// サークル
//=========================================================================*/
//MoveChanEffectCircle::MoveChanEffectCircle(math::Float2& movechan) :MoveChanEffectBall(movechan)
//{
//	m_BlueTex.Create("circle_pink.png", 5, 5);
//	m_YellowTex.Create("circle_blue.png", 5, 5);
//	m_UsingTex = m_YellowTex;
//	m_MoveChanPos = movechan;
//}
//
//void MoveChanEffectCircle::Draw()
//{
//	//Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, m_Size, &m_UsingTex, m_Color);
//}
//
///*=========================================================================
// スパーク
//=========================================================================*/
//MoveChanEffectSpark::MoveChanEffectSpark(math::Float2& movechan) :MoveChanEffect(movechan)
//{
//	std::random_device randoms;
//	std::mt19937 rando(randoms());
//
//	for (int i = 0; i < SPARK_MAX; i++)
//	{
//		m_YellowTex[i].Create("tail_yellow.png", 3, 3, m_AnimationSpeed);
//		m_BlueTex[i].Create("tail_blue.png", 3, 3, m_AnimationSpeed);
//		m_PinkTex[i].Create("tail_pink.png", 3, 3, m_AnimationSpeed);
//		m_UsingTex[i] = m_BlueTex[i];
//		m_Size[i] = m_DefinedSize;
//		m_Rot[i] = (static_cast<float>(rando() % 40)) * 0.1f;
//
//		m_Used[i] = false;
//	}
//}
//
//void MoveChanEffectSpark::Update()
//{
//	if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
//	{
//		//■スパークのセット
//		if ((rand() % 2) == 0)
//			this->Set();
//		m_Frame++;
//	}
//
//	for (int i = 0; i < SPARK_MAX; i++)
//	{
//		if (m_Used[i])
//		{
//			//アニメーションの更新
//			m_UsingTex[i].Update();
//			m_BlueTex[i].Update();
//			m_YellowTex[i].Update();
//			m_PinkTex[i].Update();
//
//			//消滅処理
//			m_FrameToDelete[i]++;
//			if (m_FrameToDelete[i] >= m_AnimationSpeed * 3)
//				m_Used[i] = false;
//
//		}
//	}
//}
//
//void MoveChanEffectSpark::Draw()
//{
//	/*for (int i = 0; i < SPARK_MAX; i++)
//	{
//		if (m_Used[i])
//		{
//			Sprite::DrawCenterK(m_Pos[i] - Stage::m_MoveNow, m_Size[i], &m_UsingTex[i], m_Color, m_Rot[i]);
//		}
//	}*/
//}
//
//void MoveChanEffectSpark::Set()
//{
//	std::random_device randoms;
//	std::mt19937 rando(randoms());
//
//	for (int i = 0; i < SPARK_MAX; i++)
//	{
//		if (!m_Used[i])
//		{
//			m_Pos[i] = Float2(m_MoveChanPos.x + m_RandomPos[i].x - 300, m_MoveChanPos.y + m_RandomPos[i].y - 300);
//			m_FrameToDelete[i] = 0;
//			m_RandomPos[i] = Float2(static_cast<float>(rando() % 600), static_cast<float>(rando() % 600));
//			m_Used[i] = true;
//			break;
//		}
//
//	}
//}
//
//
///*=========================================================================
// しっぽ
//=========================================================================*/
//MoveChanEffectTail::MoveChanEffectTail(math::Float2& movechan) :MoveChanEffect(movechan)
//{
//	for (int i = 0; i < TAIL_GROUP_MAX; i++)
//	{
//		for (int j = 0; j < TAIL_MAX; j++)
//		{
//			m_YellowTex[i][j].Create("fx_hit_test3.png", 7, 5, m_AnimationSpeed);
//			m_BlueTex[i][j].Create("fx_hit_test3.png", 7, 5, m_AnimationSpeed);
//			m_PinkTex[i][j].Create("fx_hit_test3.png", 7, 5, m_AnimationSpeed);
//			m_UsingTex[i][j] = m_YellowTex[i][j];
//			m_Used[i][j] = false;
//		}
//	}
//}
//
//MoveChanEffectTail::~MoveChanEffectTail()
//{
//}
//
//void MoveChanEffectTail::Update()
//{
//	int num = StageNum::Get() % 5;
//
//	/*static int m_Frame2, spd2 = 0;
//	if (spd % 5 == 0)
//		m_Frame++;
//	m_YellowTex.SetStartUVPosition(math::Float2(m_Frame % 7, m_Frame));*/
//
//	if (StageEnd::Get() && num == 4)
//	{
//		/// //////////////////////////////////////////テストプレイ用
//		if (Dash::Get() ||
//			(Controller::GetButtonPressRShoulder() || Input::KeyboardPress(DIK_RIGHT)) && !Dash::Get() ||
//			(Controller::GetButtonPressLShoulder() || Input::KeyboardPress(DIK_LEFT)) && !Dash::Get())
//			m_CurSpeed = MOVECHAN_EFFECT_FAST;
//		else
//			m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
//		///////////////////////////////////////////////////////////
//	}
//	else if (StageEnd::Get())
//	{
//		m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
//	}
//	else if (!StageEnd::Get() && !StageStart::Get())
//	{
//		/// //////////////////////////////////////////テストプレイ用
//		if (Dash::Get() ||
//			(Controller::GetButtonPressRShoulder() || Input::KeyboardPress(DIK_RIGHT)) && !Dash::Get() ||
//			(Controller::GetButtonPressLShoulder() || Input::KeyboardPress(DIK_LEFT)) && !Dash::Get())
//			m_CurSpeed = MOVECHAN_EFFECT_FAST;
//		else
//			m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
//		///////////////////////////////////////////////////////////
//	}
//	else
//		m_CurSpeed = MOVECHAN_EFFECT_NORMAL;
//
//
//	//■しっぽのセット
//	if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
//	{
//		if (m_Frame % m_frameToSetMoveChanEffectFast == 0)
//			this->Set();
//		m_Frame++;
//	}
//
//	if (m_CurSpeed == MOVECHAN_EFFECT_NORMAL)
//	{
//		if (m_Frame % m_frameToSetMoveChanEffectNormal == 0)
//			this->Set();
//		m_Frame++;
//	}
//
//	for (int i = 0; i < TAIL_GROUP_MAX; i++)
//	{
//		for (int j = 0; j < TAIL_MAX; j++)
//		{
//			if (m_Used[i][j])
//			{
//				//■セット後の処理
//				//アニメ-ションの更新処理
//				m_UsingTex[i][j].Update();
//
//				//サイズの変更
//				m_Size[i][j] -= m_ReducedSize;
//
//				//削除処理
//				if (m_Size[i][j].x < 0.0f)
//					m_Used[i][j] = false;
//			}
//		}
//	}
//}
//
//void MoveChanEffectTail::Draw()
//{
//	for (int i = 0; i < TAIL_GROUP_MAX; i++)
//	{
//		for (int j = 0; j < TAIL_MAX; j++)
//		{
//			if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
//			{
//				if (m_Used[i][j])
//				{
//					Sprite::DrawCenterK(m_Pos[i][j] - Stage::m_MoveNow, m_Size[i][j], &m_UsingTex[i][j], m_Color, m_Rot[i][j]);
//				}
//			}
//			if (m_CurSpeed == MOVECHAN_EFFECT_NORMAL)
//			{
//				if (j < 2)
//				{
//					Sprite::DrawCenterK(m_Pos[i][j] - Stage::m_MoveNow, m_Size[i][j], &m_UsingTex[i][j], m_Color, m_Rot[i][j]);
//				}
//			}
//		}
//	}
//}
//
//void MoveChanEffectTail::Set()
//{
//	std::random_device randoms;
//	std::mt19937 rando(randoms());
//
//	for (int i = 0; i < TAIL_GROUP_MAX; i++)
//	{
//		if (!m_Used[i][0])
//		{
//			for (int j = 0; j < TAIL_MAX; j++)
//			{
//				if (rando() % 5 == 0)
//					m_UsingTex[i][j] = m_BlueTex[i][j];
//				else
//					m_UsingTex[i][j] = m_YellowTex[i][j];
//
//				if (m_CurSpeed == MOVECHAN_EFFECT_FAST)
//				{
//					if (rando() % 5 == 0)
//						m_UsingTex[i][j] = m_PinkTex[i][j];
//					else
//						m_UsingTex[i][j] = m_BlueTex[i][j];
//				}
//
//				m_Pos[i][j] = Float2(m_MoveChanPos.x + static_cast<float>(rando() % 100) - 50, m_MoveChanPos.y + static_cast<float>(rando() % 100) - 50);
//				m_Size[i][j] = m_DefinedSize;
//				m_Rot[i][j] = (static_cast<float>(rando() % 40)) * 0.1f;
//				m_Used[i][j] = true;
//
//				m_UsingTex[i][j].SetCurrentTexture(rando() % 10);
//			}
//			break;
//		}
//	}
//}
//
///*=========================================================================
// BG
//=========================================================================*/
//MoveChanEffectBG::MoveChanEffectBG(math::Float2& movechan) : MoveChanEffect(movechan)
//{
//	m_Tex.Create("result_bg.png", 1, 1);
//	m_Color = { 0.0f,0.0f,0.0f,m_AlphaMax };
//}
//
//MoveChanEffectBG::~MoveChanEffectBG()
//{
//}
//
//void MoveChanEffectBG::Update()
//{
//	//スピードが上がると暗くなる
//	if (m_MoveChanSpd == MOVECHAN_EFFECT_FAST)
//	{
//		m_Color.w += 0.01f;
//		if (m_Color.w > m_AlphaMax)
//			m_Color.w = m_AlphaMax;
//	}
//	if (m_MoveChanSpd == MOVECHAN_EFFECT_NORMAL)
//	{
//		m_Color.w -= 0.01f;
//		if (m_Color.w < 0.0f)
//			m_Color.w = 0.0f;
//	}
//
//}
//
//void MoveChanEffectBG::Draw()
//{
//	Sprite::DrawCenter(m_Pos, m_Size, &m_Tex, m_Color);
//}
//
//void MoveChanEffectBG::SetSpd(MOVECHAN_EFFECT_SPEED ms)
//{
//	m_MoveChanSpd = ms;
//}
//
