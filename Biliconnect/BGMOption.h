
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
		void Init();	//����������
		void Uninit();	//�I������
		void Update();	//�X�V����
		void Draw();	//�`�揈��
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

		//BGM��SE����
		enum {
			VOLUME_0,
			VOLUME_20,
			VOLUME_40,
			VOLUME_60,
			VOLUME_80,
			VOLUME_100,
			VOLUME_INDEX_MAX,
		};

		//BGM�̓��͒���SE�̓��͒���
		typedef enum {
			SELECT_BGM,
			SELECT_SE,
			SELECT_BACK,
		}SELECT;

		//���͂��Ă������(���ʂ��グ������������)
		typedef enum {
			RIGHT,
			LEFT,
		}INPUT_MODE;	

		//�g�p�e�N�X�`���C���f�b�N�X
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


		float m_SP[VOLUME_INDEX_MAX], m_GS[VOLUME_INDEX_MAX],m_GP[VOLUME_INDEX_MAX];//�X�t�B�A�|�W�V�����ƃO���[���|�W�V�����ƃO���[���T�C�Y
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


