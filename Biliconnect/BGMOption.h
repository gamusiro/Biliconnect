
#ifndef BGMOPTION_H_
#define BGMOPTION_H_

#include "GameCreateSystem.h"
#include "SceneInterface.h"

class BGMOption
{
	public:
		BGMOption();
		~BGMOption();
	
	public:
		void Init();	//初期化処理
		void Uninit();	//終了処理
		void Update();	//更新処理
		void Draw();	//描画処理
		void OperateOption(bool tf);
		bool GetOperateOption();
		bool Get() { return canOperateOption; }
		bool GetSE() { return canOperateSE; }
		bool GetBGM() { return canOperateBGM; }
		int GetSelect() { return (int)m_Select; }
		void DrawNum(int Num, bool se_bgm);
		int GetFrameSinceInputBack() { return m_FrameSinceInputBack; }
		void Back(bool tf) { 
			if(tf)
			m_back = true;
			else if(!tf)
				m_back = false;
		}
	private:

		//BGMとSE音量
		enum {
			VOLUME_0,
			VOLUME_20,
			VOLUME_40,
			VOLUME_60,
			VOLUME_80,
			VOLUME_100,
			VOLUME_INDEX_MAX,
		};

		//BGMの入力中かSEの入力中か
		typedef enum {
			SELECT_BGM,
			SELECT_SE,
			SELECT_BACK,
		}SELECT;

		//入力している方向(音量を上げたか下げたか)
		typedef enum {
			RIGHT,
			LEFT,
		}INPUT_MODE;	

		//使用テクスチャインデックス
		enum {
			WAKU,
			BGM_GREEN,
			BGM_LIGHT,
			BGM_WAKU,
			BGM_SPHERE,
			SE_GREEN,
			SE_LIGHT,
			SE_WAKU,
			SE_SPHERE,
			BACK,
			MAX,
		};



		Texture* m_Tex[MAX];
		math::Float2 m_Pos[MAX], m_Vel[MAX], m_Size[MAX];
		math::Float4 m_Color[MAX];
		int          m_Frame;

		int          m_BGMVolume, m_SEVolume;

		SELECT m_Select;
		INPUT_MODE m_BGMInputMode, m_SEInputMode;


		float m_SP[VOLUME_INDEX_MAX], m_GS[VOLUME_INDEX_MAX],m_GP[VOLUME_INDEX_MAX];//スフィアポジションとグリーンポジションとグリーンサイズ
		bool canOperateBGM, canOperateSE,canOperateOption;

		const math::Float2 LIGHT_SIZE = math::Float2(1433.0f * 1.25f, 200.0f * 1.36f);

		Texture* m_TexBGMNum;
		int m_DefineSoundNum[VOLUME_INDEX_MAX];


		int m_BGMNum, m_SENum;
		int m_BGMNumIniPos, m_SENumIniPos;

		bool m_back;
		int m_FrameSinceInputBack;

		bool first = true;



};




#endif // !BGMOPTION_H_


