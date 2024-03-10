/*=========================================================================
	Date : 2022/03/11(金)	Stage.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef STAGE_H_
#define STAGE_H_

#include <memory>
#include <vector>
#include "GameCreateSystem.h"
#include "SaveStage.h"
class PlayerManager;
class MoveChan;
class MoveChanEffectBall;
class MoveChanEffectCircle;
class MoveChanEffectSpark;
class MoveChanEffectTail;
class DefeatEffect;
class DefeatEffect2;
class DefeatEffect3;
class CharacterEffect;
class GoalEffect;
class LineEffect;
class Line;
class BG;
class Bug;
class Timer;
class Score;
class SState;
class HitStop;
class ObjectManager;
class StageTelop;
class BossBlock;
class Tutorial;

class Stage
{
public:
	Stage();
	~Stage();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ChangeState(SState* state);
	static void SetShake(math::Float2 shake) {
		m_Shake = shake;
	}

private:
	constexpr static int PLAYER_NUM = 2;	// 動かすやつの数
	constexpr static int BLOCK_NUM = 50;	// ブロック数

private:
	std::unique_ptr<PlayerManager>  	 m_PlayerManager;
	std::unique_ptr<Line>			     m_Line;
	std::unique_ptr<MoveChan>		     m_MoveChan;

	std::unique_ptr<LineEffect>	         m_LineEffect;        ///////////////
	std::unique_ptr<DefeatEffect>	     m_DEffect;        ///////////////
	std::unique_ptr<DefeatEffect2>	     m_DEffect2;        ///////////////
	std::unique_ptr<DefeatEffect3>	     m_DEffect3;        ///////////////
	std::unique_ptr<CharacterEffect>	 m_CharacterEffect; //////////////
	
 
	std::unique_ptr<Timer>			m_Timer;
	std::unique_ptr<Score>			m_Score;

	std::unique_ptr<ObjectManager>	m_ObjM;
	std::unique_ptr<BossBlock>	m_BB;

	std::unique_ptr<BG>	m_BG;
	std::unique_ptr<Bug>	m_Bug;
	std::unique_ptr<StageTelop>	m_ST;
	std::unique_ptr<Tutorial>	m_TR;
	//std::vector <std::unique_ptr<BG>> m_BG;
	SaveStage::NowData m_Data;	// 現在のステージのデータ変数

private:
	float m_Center;					// 画面中心にする座標
	
public:
	static float m_MoveMax;				// 移動限界
	static math::Float2 m_MoveNow;		// 現在移動値

	std::unique_ptr<SState> m_State;
	std::unique_ptr<HitStop>m_HitStop;
	static math::Float2 m_Shake;
};

__declspec(selectany) float Stage::m_MoveMax(0);
__declspec(selectany) math::Float2 Stage::m_MoveNow(math::Float2(0, 0));
__declspec(selectany) math::Float2 Stage::m_Shake(math::Float2(0, 0));

class StageNum
{
public:
	static int Num;

	static void Set(int stagenum)	{ Num = stagenum; }
	static int	Get(void)			{ return Num; }
	static void Next() { Num += 1; }
};
__declspec(selectany) int StageNum::Num(0);

class StageStart
{
private:
	static int timer;
	static bool isStart;

public:
	static void	Update(void);
	static void	Reset(void) { isStart = true; timer = 0; };
	static bool	Get(void) { return isStart; }
	static int	GetTimer(void) { return timer; }
};
__declspec(selectany) int StageStart::timer(0);
__declspec(selectany) bool StageStart::isStart(true);

class StageEnd
{
private:
	static bool isEnd;

public:
	static void	Set(void) { isEnd = true; };
	static void	Reset(void) { isEnd = false; };
	static bool	Get(void) { return isEnd; }
};
__declspec(selectany) bool StageEnd::isEnd(false);
#endif
