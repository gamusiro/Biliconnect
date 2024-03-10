#include "BGMOption.h"
#include "Volume.h"
#include "SEManager.h"
using namespace math;

BGMOption::BGMOption()
{
	for (int i = 0; i < MAX; i++)
	{
		m_Tex[i] = new Texture();
	}
	m_TexBGMNum = new Texture();
}

BGMOption::~BGMOption()
{
}

void BGMOption::Init()
{

	//最初の音量を設定する
	int FirstBGMVolume = Volume::GetBGM();//BGMの初期値
	int FirstSEVolume = Volume::GetSE();//SEの初期値

	if (first)
	{
		for (int i = 0; i < VOLUME_INDEX_MAX; i++)
		{
			m_SP[i] = 500.0f + 185.0f * i;
			m_GS[i] = 185.0f * i;
			m_GP[i] = 485.0f + i * 90 + 5;
			m_DefineSoundNum[i] = i * 20;

		}

		m_Tex[WAKU]->Create("Option/option_ground.png", 1, 1);
		m_Pos[WAKU] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
		m_Size[WAKU] = Float2(1920.0f, 1080.0f);
		m_Color[WAKU] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Tex[BGM_GREEN]->Create("result_bg.png", 1, 1);
		m_Pos[BGM_GREEN] = Float2(m_GP[FirstBGMVolume], SCREEN_HEIGHT * 0.5f - 240.0f);
		m_Size[BGM_GREEN] = Float2(m_GS[FirstBGMVolume], 50.0f);
		m_Color[BGM_GREEN] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Tex[BGM_WAKU]->Create("Option/bgmvolume.png", 1, 1);
		m_Pos[BGM_WAKU] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 240.0f);
		m_Size[BGM_WAKU] = Float2(1433, 200.0f);
		m_Color[BGM_WAKU] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Tex[BGM_SPHERE]->Create("Option/soundvolume_point.png", 1, 1);
		m_Pos[BGM_SPHERE] = Float2(m_SP[FirstBGMVolume], SCREEN_HEIGHT * 0.5f - 240.0f);
		m_Size[BGM_SPHERE] = Float2(60.0f, 110.0f);
		m_Color[BGM_SPHERE] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Tex[BGM_LIGHT]->Create("Option/volume_01.png", 1, 1);
		m_Pos[BGM_LIGHT] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 240.0f);
		m_Size[BGM_LIGHT] = LIGHT_SIZE;
		m_Color[BGM_LIGHT] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Tex[SE_GREEN]->Create("result_bg.png", 1, 1);
		m_Pos[SE_GREEN] = Float2(m_GP[FirstSEVolume], SCREEN_HEIGHT * 0.5f - 0.0f);
		m_Size[SE_GREEN] = Float2(m_GS[FirstSEVolume], 50.0f);
		m_Color[SE_GREEN] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Tex[SE_WAKU]->Create("Option/sevolume.png", 1, 1);
		m_Pos[SE_WAKU] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
		m_Size[SE_WAKU] = Float2(1433.0f, 200.0f);
		m_Color[SE_WAKU] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Tex[SE_SPHERE]->Create("Option/soundvolume_point.png", 1, 1);
		m_Pos[SE_SPHERE] = Float2(m_SP[FirstSEVolume], SCREEN_HEIGHT * 0.5f);
		m_Size[SE_SPHERE] = Float2(60.0f, 110.0f);
		m_Color[SE_SPHERE] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Tex[SE_LIGHT]->Create("Option/volume_01.png", 1, 1);
		m_Pos[SE_LIGHT] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
		m_Size[SE_LIGHT] = LIGHT_SIZE;
		m_Color[SE_LIGHT] = Float4(1.0f, 1.0f, 1.0f, 0.0f);

		m_Tex[BACK]->Create("Button/back_icon.png", 3, 1);
		m_Pos[BACK] = Float2(SCREEN_WIDTH * 0.5f - 480.0f, SCREEN_HEIGHT * 0.5f + 240.0f);
		m_Size[BACK] = Float2(600.0f * 0.9f, 200.0f * 0.9f);
		m_Color[BACK] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		m_BGMVolume = FirstBGMVolume;
		m_SEVolume = FirstSEVolume;
		m_Select = SELECT_BGM;
		m_BGMInputMode = RIGHT;


		m_TexBGMNum->Create("Option/option_number_icon.png", 10, 1);

		canOperateOption = false;


		m_BGMNum = m_DefineSoundNum[m_BGMVolume];
		m_SENum = m_DefineSoundNum[m_BGMVolume];
		first = false;
	}

	m_back = false;

}

void BGMOption::Uninit()
{
}


void BGMOption::Update()
{
	if (!m_back)
	{
		m_FrameSinceInputBack = 0;
	}
	else
	{
		m_FrameSinceInputBack++;
	}

	if (canOperateOption)
	{
		//■入力設定===================================================================
		//音量操作中は項目選択中不可能。また、項目選択中は音量調整不可能


		//右を押したら

		if (Controller::GetLStickTriggerRight() || Controller::GetButtonTriggerRight())
		{
			//BGMを選択時
			if (m_Select == SELECT_BGM)
			{

				//音量が100未満なら
				if (m_BGMVolume < VOLUME_100)
				{
					m_BGMVolume++;//音量を上げる
					m_BGMInputMode = RIGHT;
				}

			}
			//SEを選択時
			if (m_Select == SELECT_SE)
			{

				//音量が100未満なら
				if (m_SEVolume < VOLUME_100)
				{
					m_SEVolume++;//音量を上げる
					m_SEInputMode = RIGHT;

				}
				switch (m_SEVolume)
				{
				case VOLUME_0:
					Volume::SetSE(0); break;
					;
				case VOLUME_20:
					Volume::SetSE(1); break;
					;
				case VOLUME_40:
					Volume::SetSE(2); break;
					;
				case VOLUME_60:
					Volume::SetSE(3); break;
					;
				case VOLUME_80:
					Volume::SetSE(4); break;
					;
				case VOLUME_100:
					Volume::SetSE(5); break;
					;
				default:
					;
				};
				SEManager::Play(SOUND::DECISION);
			}

		}

		//左を押したら
		if (Controller::GetLStickTriggerLeft() || Controller::GetButtonTriggerLeft())
		{
			//BGMを選択時
			if (m_Select == SELECT_BGM)
			{

				//音量が0より上なら
				if (m_BGMVolume > VOLUME_0)
				{
					m_BGMVolume--;//音量を下げる
					m_BGMInputMode = LEFT;
				}

			}

			//SEを選択時
			if (m_Select == SELECT_SE)
			{

				//音量が100未満なら
				if (m_SEVolume > VOLUME_0)
				{
					m_SEVolume--;//音量を下げる
					m_SEInputMode = LEFT;
				}
				switch (m_SEVolume)
				{
				case VOLUME_0:
					Volume::SetSE(0); break;
					;
				case VOLUME_20:
					Volume::SetSE(1); break;
					;
				case VOLUME_40:
					Volume::SetSE(2); break;
					;
				case VOLUME_60:
					Volume::SetSE(3); break;
					;
				case VOLUME_80:
					Volume::SetSE(4); break;
					;
				case VOLUME_100:
					Volume::SetSE(5); break;
					;
				default:
					;
				};
				SEManager::Play(SOUND::DECISION);
			}
		}


		//上を押したら
		if (Controller::GetLStickTriggerUp() || Controller::GetButtonTriggerUp())
		{
			//SE選択時
			if (m_Select == SELECT_SE)
			{
				SEManager::Play(SOUND::CURSOR);
				m_Select = SELECT_BGM;//選択項目をBGMにする
			}
			else
				//BACK選択時
				if (m_Select == SELECT_BACK)
				{
					SEManager::Play(SOUND::CURSOR);
					m_Select = SELECT_SE;//選択項目をSEにする
				}
		}

		//下を押したら
		if (Controller::GetLStickTriggerDown() || Controller::GetButtonTriggerDown())
		{
			//BGM選択時
			if (m_Select == SELECT_BGM)
			{
				SEManager::Play(SOUND::CURSOR);
				m_Select = SELECT_SE;//選択項目をSEにする
			}
			else
				//SE選択時
				if (m_Select == SELECT_SE)
				{
					SEManager::Play(SOUND::CURSOR);
					m_Select = SELECT_BACK;//選択項目をBACKにする
				}
		}


		//■入力設定===================================================================
		//■アニメーション設定=========================================================


		float ScrollSpeed = 20.0f;
		float ScrollSpeed2 = 20.0f;
		if (m_BGMInputMode == RIGHT)
		{
			//スフィアのスクロール
			if (m_Pos[BGM_SPHERE].x < m_SP[m_BGMVolume])
				m_Pos[BGM_SPHERE].x += ScrollSpeed;

			//バーのスクロール
			if (m_Size[BGM_GREEN].x < m_GS[m_BGMVolume])
			{
				m_Size[BGM_GREEN].x += ScrollSpeed2;
				m_Pos[BGM_GREEN].x += ScrollSpeed2 * 0.5f;
			}
		}

		if (m_BGMInputMode == LEFT)
		{
			if (m_Pos[BGM_SPHERE].x > m_SP[m_BGMVolume])
				m_Pos[BGM_SPHERE].x -= ScrollSpeed;

			if (m_Size[BGM_GREEN].x > m_GS[m_BGMVolume])
			{
				m_Size[BGM_GREEN].x -= ScrollSpeed2;
				m_Pos[BGM_GREEN].x -= ScrollSpeed2 * 0.5f;
			}


		}

		if (m_SEInputMode == RIGHT)
		{
			if (m_Pos[SE_SPHERE].x < m_SP[m_SEVolume])
				m_Pos[SE_SPHERE].x += ScrollSpeed;

			if (m_Size[SE_GREEN].x < m_GS[m_SEVolume])
			{
				m_Size[SE_GREEN].x += ScrollSpeed2;
				m_Pos[SE_GREEN].x += ScrollSpeed2 * 0.5f;
			}


		}

		if (m_SEInputMode == LEFT)
		{
			if (m_Pos[SE_SPHERE].x > m_SP[m_SEVolume])
				m_Pos[SE_SPHERE].x -= ScrollSpeed;

			if (m_Size[SE_GREEN].x > m_GS[m_SEVolume])
			{
				m_Size[SE_GREEN].x -= ScrollSpeed2;
				m_Pos[SE_GREEN].x -= ScrollSpeed2 * 0.5f;
			}
		}

		//ボタンの色
		if (!m_back) {
			if (m_Select == SELECT_BGM)
			{
				m_Tex[BACK]->SetStartUVPosition(math::Float2(0.0f, 1.0f));

				m_Color[BGM_LIGHT].w += 0.1f;
				if (m_Color[BGM_LIGHT].w > 1.0f)
					m_Color[BGM_LIGHT].w = 1.0f;

				m_Color[SE_LIGHT].w -= 0.1f;
				if (m_Color[SE_LIGHT].w < 0.0f)
					m_Color[SE_LIGHT].w = 0.0f;
			}
			if (m_Select == SELECT_SE)
			{
				m_Tex[BACK]->SetStartUVPosition(math::Float2(0.0f, 1.0f));

				m_Color[SE_LIGHT].w += 0.1f;
				if (m_Color[SE_LIGHT].w > 1.0f)
					m_Color[SE_LIGHT].w = 1.0f;

				m_Color[BGM_LIGHT].w -= 0.1f;
				if (m_Color[BGM_LIGHT].w < 0.0f)
					m_Color[BGM_LIGHT].w = 0.0f;
			}
			if (m_Select == SELECT_BACK)
			{
				m_Color[SE_LIGHT].w -= 0.1f;
				if (m_Color[SE_LIGHT].w < 0.0f)
					m_Color[SE_LIGHT].w = 0.0f;
				m_Tex[BACK]->SetStartUVPosition(math::Float2(0.3333333333333f, 1.0f));

			}


		}
		else if (m_back)
		{
			m_Tex[BACK]->SetStartUVPosition(Float2(0.6666666f, 0.0f));
		}



		//数値
		//右キーが押されたとき
		if (m_BGMInputMode == RIGHT)
		{
			//BGMの数字のカウントアップダウン
			m_BGMNum++;
			if (m_BGMNum > m_DefineSoundNum[m_BGMVolume])
				m_BGMNum = m_DefineSoundNum[m_BGMVolume];
		}

		//左キーが押されたとき
		if (m_BGMInputMode == LEFT)
		{
			//BGMの数字のカウントアップダウン
			m_BGMNum--;
			if (m_BGMNum < m_DefineSoundNum[m_BGMVolume])
				m_BGMNum = m_DefineSoundNum[m_BGMVolume];

		}
		if (m_SEInputMode == RIGHT)
		{
			//BGMの数字のカウントアップダウン
			m_SENum++;
			if (m_SENum > m_DefineSoundNum[m_SEVolume])
				m_SENum = m_DefineSoundNum[m_SEVolume];
		}

		//左キーが押されたとき
		if (m_SEInputMode == LEFT)
		{
			//BGMの数字のカウントアップダウン
			m_SENum--;
			if (m_SENum < m_DefineSoundNum[m_SEVolume])
				m_SENum = m_DefineSoundNum[m_SEVolume];
		}


		//■アニメーション設定=========================================================
		//■音量設定===================================================================
		switch (m_BGMVolume)
		{
		case VOLUME_0:
			Volume::SetBGM(0);
			break;
			;
		case VOLUME_20:
			Volume::SetBGM(1); break;
			;
		case VOLUME_40:
			Volume::SetBGM(2); break;
			;
		case VOLUME_60:
			Volume::SetBGM(3); break;
			;
		case VOLUME_80:
			Volume::SetBGM(4); break;
			;
		case VOLUME_100:
			Volume::SetBGM(5); break;
			;
		default:
			;
		};

		switch (m_SEVolume)
		{
		case VOLUME_0:
			Volume::SetSE(0); break;
			;
		case VOLUME_20:
			Volume::SetSE(1); break;
			;
		case VOLUME_40:
			Volume::SetSE(2); break;
			;
		case VOLUME_60:
			Volume::SetSE(3); break;
			;
		case VOLUME_80:
			Volume::SetSE(4); break;
			;
		case VOLUME_100:
			Volume::SetSE(5); break;
			;
		default:
			;
		};
		//■音量設定===================================================================
	}
}

void BGMOption::Draw()
{
	if (canOperateOption)
	{
		for (int i = 0; i < MAX; i++)
		{
			Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Color[i]);
		}
	}


	DrawNum(m_BGMNum, 0);
	DrawNum(m_SENum, 1);
}

void BGMOption::OperateOption(bool tf)
{
	canOperateOption = tf;
	m_Select = SELECT_BGM;
}

bool BGMOption::GetOperateOption()
{
	return canOperateOption;
}

void BGMOption::DrawNum(int Num, bool se_bgm)
{
	int SoundNumA = Num;//一桁目を取り出す
	float SoundNumB;
	int m_Digit = 2;

	//桁数
	if (SoundNumA < 10)
		m_Digit = 1;
	else if (SoundNumA >= 10 && SoundNumA < 100)
		m_Digit = 2;
	else if (SoundNumA == 100)
	{
		m_Digit = 3;
	}

	//右キーが押されたとき
	if (m_BGMInputMode == RIGHT)
	{
		if (se_bgm == 0)
		{
			//数字の位置のズレ
			if (SoundNumA > 80)
			{
				m_BGMNumIniPos += 5.0f;
				if (m_BGMNumIniPos > 32.0f)
					m_BGMNumIniPos = 32.0f;
			}

			if (SoundNumA > 0 && SoundNumA <= 80)
			{
				m_BGMNumIniPos += 5.0f;
				if (m_BGMNumIniPos > 0.0f)
					m_BGMNumIniPos = 0.0f;
			}
		}
	}

	//左キーが押されたとき
	if (m_BGMInputMode == LEFT)
	{
		if (se_bgm == 0)
		{
			//数字の位置のズレ
			if (SoundNumA >= 20 && SoundNumA < 100)
			{
				m_BGMNumIniPos -= 5.0f;
				if (m_BGMNumIniPos < 0.0f)
					m_BGMNumIniPos = 0.0f;
			}

			if (SoundNumA < 20)
			{
				m_BGMNumIniPos -= 5.0f;
				if (m_BGMNumIniPos < -32.0f)
					m_BGMNumIniPos = -32.0f;
			}
		}

	}

	//右キーが押されたとき
	if (m_SEInputMode == RIGHT)
	{
		if (se_bgm == 1)
		{
			//数字の位置のズレ
			if (SoundNumA > 80)
			{
				m_SENumIniPos += 5.0f;
				if (m_SENumIniPos > 32.0f)
					m_SENumIniPos = 32.0f;
			}

			if (SoundNumA > 0 && SoundNumA <= 80)
			{
				m_SENumIniPos += 5.0f;
				if (m_SENumIniPos > 0.0f)
					m_SENumIniPos = 0.0f;
			}
		}
	}

	//左キーが押されたとき
	if (m_SEInputMode == LEFT)
	{
		if (se_bgm == 1)
		{

			//数字の位置のズレ
			if (SoundNumA >= 20 && SoundNumA < 100)
			{
				m_SENumIniPos -= 5.0f;
				if (m_SENumIniPos < 0.0f)
					m_SENumIniPos = 0.0f;
			}

			if (SoundNumA < 20)
			{
				m_SENumIniPos -= 5.0f;
				if (m_SENumIniPos < -32.0f)
					m_SENumIniPos = -32.0f;
			}
		}
	}


	if (se_bgm == 0)
	{
		for (int i = 0; i < m_Digit; i++)
		{
			SoundNumB = (float)(SoundNumA % 10);
			m_TexBGMNum->SetStartUVPosition(Float2((1.0f / 10.0f) * SoundNumB, 0.0f));

			Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.2f + (1190.0f + m_BGMNumIniPos) - i * 60.0f, SCREEN_HEIGHT * 0.2f + 80.0f),
				Float2(70.0f, 70.0f), m_TexBGMNum, Float4(1.0f, 1.0f, 1.0f, 1.0f));


			SoundNumA /= 10;
		}
	}
	if (se_bgm == 1)
	{
		for (int i = 0; i < m_Digit; i++)
		{
			SoundNumB = (float)(SoundNumA % 10);
			m_TexBGMNum->SetStartUVPosition(Float2((1.0f / 10.0f) * SoundNumB, 0.0f));

			Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.2f + (1190.0f + m_SENumIniPos) - i * 60.0f, SCREEN_HEIGHT * 0.2f + 320.0f),
				Float2(70.0f, 70.0f), m_TexBGMNum, Float4(1.0f, 1.0f, 1.0f, 1.0f));


			SoundNumA /= 10;
		}
	}
}

