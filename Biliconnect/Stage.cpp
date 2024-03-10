/*=========================================================================
	Date : 2022/03/11(金)	Stage.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "Stage.h"
#include "Game.h"

using namespace math;

#include "PlayerManager.h"
#include "Line.h"
#include "LineEffect.h"
#include "Goaleffect.h"
#include "MoveChan.h"
#include "DefeatEffect.h"
#include "GoalEffect.h"
#include "HitStop.h"
#include "SState.h"
#include "SState_Nomal.h"
#include "ObjectManager.h"
#include "Coin.h"
#include "StageTelop.h"

#include "LoadChip.h"

#include "BG.h"
#include "Bug.h"
#include "StageTelop.h"
#include "Timer.h"
#include "Score.h"
#include "SaveStage.h"
#include "EnemyNum.h"
#include "Coin.h"
#include "SEManager.h"
#include "BossBlock.h"
#include "Tutorial.h"



using std::make_unique;

Stage::Stage()
	:m_State(new SState_Nomal(*this)),
	m_ObjM(nullptr), m_Center(0)
{
	//StageNum::Set(25);
	m_Timer = make_unique<Timer>();
	m_Score = make_unique<Score>();

	m_PlayerManager = make_unique<PlayerManager>();
	m_Line			= make_unique<Line>(m_PlayerManager->GetLeftPos(), m_PlayerManager->GetRightPos());
	m_MoveChan		= make_unique<MoveChan>(Float2(SCREEN_WIDTH * 0.5f, -600), *m_Line.get());
	m_BG		    = std::make_unique<BG>(*m_MoveChan.get());
	m_Bug			= std::make_unique<Bug>(*m_MoveChan.get());
	m_ST			= std::make_unique<StageTelop>();
	m_TR			= std::make_unique<Tutorial>();
	m_HitStop	    = std::make_unique<HitStop>();

	// objload 後で編集
	LoadChip lc;

	m_DEffect.reset(new DefeatEffect());
	m_DEffect2.reset(new DefeatEffect2());
	m_DEffect3.reset(new DefeatEffect3());
	m_CharacterEffect.reset(new CharacterEffect());


	Dash::Set(false);
	StageEnd::Reset();
	StageStart::Reset();
	Coin::Reset();// コイン枚数リセット
	EnemyNum::Reset();// 敵の数をリセット
	m_ObjM = std::make_unique<ObjectManager>(lc.LoadChips(0, *m_MoveChan.get()), *m_MoveChan.get(), *m_DEffect.get(), *m_DEffect2.get(), *m_DEffect3.get(), *m_CharacterEffect.get());// Get

	m_MoveMax = lc.GetStageY();////// 要変更

	m_BB = std::make_unique<BossBlock>(*m_MoveChan.get());// Get

	// ステージデータ初期化
	m_Data.coin = 0;
	m_Data.kill = 0;
	m_Data.life = 0;
	m_Data.enemymax = 0;

	SaveStage::Set(StageNum::Get(), m_Data);// Get ステージデータ初期化
}

Stage::~Stage()
{
}

void Stage::Init()
{
	// effect
	{
		m_LineEffect.reset(new LineEffect(m_MoveChan->GetPos(), m_Line.get()));
	}

	m_ObjM->Init();

	m_DEffect->Init();
	//m_DEffect2->Init();
	m_DEffect3->Init();
	m_CharacterEffect->Init();
	m_TR->Init();

    //for (int i = 0; m_MoveMax > i * SCREEN_HEIGHT + 1; i++)
		//m_BG.push_back(std::make_unique<BG>(i));

	m_MoveNow = { 0, m_Center };
}

void Stage::Uninit()
{
	m_TR->Uninit();
}

void Stage::Update()
{
	// スタートの演出
	if (StageStart::Get())
		StageStart::Update();

	m_TR->Update();
	m_HitStop->Update();// ヒットストップ管理
	m_State->Update();
	m_Score->Update();
	m_DEffect->Update();
	m_DEffect2->Update();
	m_DEffect3->Update();
	m_CharacterEffect->Update();

	/*if (Controller::GetButtonReleaseX())
		m_Bug->Delete();*/

	if (HitStop::Get() <= 0)
	{
		m_ObjM->Update();

		m_PlayerManager->Update();
		m_Line->Update();

		m_MoveChan->Update();


		m_Timer->Update();
		m_BG->Update();

		int num = StageNum::Get() % 5;
		if (num == 4)
		{
			m_BB->Update();
			m_BB->CheckCollision(*m_MoveChan.get(), *m_Bug.get());
			m_Bug->Update();
		}
		
		if (num == 4 && StageStart::GetTimer() > 120 && StageStart::GetTimer() < 600)
		{
			m_ST->Update();
		}
		else if (StageStart::GetTimer() > 120 && StageStart::GetTimer() < 400)
		{
			m_ST->Update();
		}

	/*	if(Controller::GetButtonTriggerA())
			Fade::Transition(SCENE_TYPE::RESULT, FADE_TYPE::STAIR, nullptr, Float3(1, 1, 0.3f));*/

		// スクロール
		if (!m_MoveChan->GetDeath() && !StageStart::Get())
		{
			if (m_MoveNow.y - m_Shake.y < m_MoveMax - SCREEN_HEIGHT)
			{
				if(StageNum::Get() == 23)
					m_Center += 6.f;
				else
					m_Center += 4.f;
				m_MoveNow = { m_Shake.x, m_Center + m_Shake.y };
			}
			else
			{
				Controller::StopVibration();
				static int timer = 0;
				int num = StageNum::Get() % 5;
				timer++;

				StageEnd::Set();
				if(num != 4)
					m_MoveChan->SetAnimation(ANIMATION::SMILE);
				m_MoveNow.y = m_MoveMax - SCREEN_HEIGHT - m_Shake.y;

				if(num == 4)
				{
					timer = 0;

					m_Data.coin = Coin::Get();
					m_Data.kill = EnemyNum::GetKill();
					m_Data.life = m_MoveChan->GetLife();
					m_Data.enemymax = EnemyNum::Get();

					SaveStage::Set(StageNum::Get(), m_Data);// Get

					if(m_BB->GetTimer() > 240 && Fade::GetState())
						Fade::Transition(SCENE_TYPE::RESULT, FADE_TYPE::STAIR, nullptr, Float3(1, 1, 0.3f));
				}
				else if (timer > 120 && Fade::GetState() && num != 4)
				{
					timer = 0;

					m_Data.coin = Coin::Get();
					m_Data.kill = EnemyNum::GetKill();
					m_Data.life = m_MoveChan->GetLife();
					m_Data.enemymax = EnemyNum::Get();

					SaveStage::Set(StageNum::Get(), m_Data);// Get

					Fade::Transition(SCENE_TYPE::RESULT, FADE_TYPE::STAIR, nullptr, Float3(1, 1, 0.3f));
				}
			}
		}

		// スクロールロック
		if (m_MoveNow.y + m_Shake.y < 0) m_MoveNow.y = 0 + m_Shake.y;
	}
}

void Stage::Draw()
{
	printf("%d", Coin::Get());

	m_BG->Draw();

	//m_Timer->Draw();
	m_BG->Draw2();
	m_DEffect3->Draw();


	int num = StageNum::Get() % 5;
	if (num == 4)
	{
		m_Bug->Draw2();
		m_BB->Draw();
	}
	
	m_ObjM->Draw();
	if (num == 4)
		m_Bug->Draw();
	if (!StageStart::Get())
		m_TR->Draw();
	m_DEffect->Draw();
	m_Score->Draw();

	m_Line->Draw();
	m_DEffect2->Draw();
	m_PlayerManager->Draw();


	m_MoveChan->Draw();
	m_CharacterEffect->Draw();

	if (num == 4 && StageStart::GetTimer() > 120 && StageStart::GetTimer() < 600)
	{
		m_ST->Draw();
	}
	else if (StageStart::GetTimer() > 120 && StageStart::GetTimer() < 400)
	{
		m_ST->Draw();
	}
	if(Game::GetGameState() == 1)
	m_ST->Draw2();
}

void Stage::ChangeState(SState* state)
{
	m_State.reset(state);
}

void StageStart::Update(void)
{
	timer++;

	int num = StageNum::Get() % 5;
	if (num == 4)
	{
		if (timer > 250)
		{
			StageTelop::SetWarning();
		}
		if (timer == 280)
		{
			SEManager::Play(SOUND::WARNING);
		}
		if (timer > 330)
		{
			if (Controller::GetButtonTriggerB())
			{
				timer = 600;
				Bug::Set();
				SEManager::Stop(SOUND::WARNING);
			}
		}
		if (timer > 600)
		{
			timer = 0;
			isStart = false;
		}
	}
	else if (num != 4)
	{
		if (timer > 270)
		{
			timer = 0;
			isStart = false;
		}
	}
}

