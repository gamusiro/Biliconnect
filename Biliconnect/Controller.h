/*=============================================================================================================
	Controller.cpp (Xinputを利用)
				Author	:	白 人

				Create	:	2021/11/09
				Update	:	2022/04/05
=============================================================================================================*/
#ifndef Controller_H_
#define Controller_H_

#include <Windows.h>
#include "Original/MathManager.h"

#include "XInput.h"
#pragma comment(lib, "xinput.lib")

class Controller
{
public:
	//Xinputを利用する(main.cppに書くもの)
	static void Init();		//初期化
	static void Uninit();	//終了処理
	static void Update();	//更新処理

public:
	//コントローラーの振動
	static void SetVibration	 (UINT val);	//両方振動(0～)
	static void SetVibrationRight(UINT val);	//右側のみ振動
	static void SetVibrationLeft (UINT val);	//左側のみ振動
	static void StopVibration();				//振動の停止(振動書いたら呼ばないと止まらないよテヘペロ)

public:
	//Stickの値を取得
	static math::Float2 GetLeftStick();			//DeadZoneは-0.1f～0.1f場合(Float2がない場合はD3DVECTOR2を使えばOK!)
	static math::Float2 GetRightStick();		//DeadZoneは-0.1f～0.1f場合(Float2がない場合はD3DVECTOR2を使えばOK!)

public:
	static bool GetLStickPressUp();			//LStickのUp
	static bool GetLStickPressDown();		//LStickのDown
	static bool GetLStickPressRight();		//LStickのRight
	static bool GetLStickPressLeft();		//LStickのLeft
	static bool GetRStickPressUp();			//RStickのUp
	static bool GetRStickPressDown();		//RStickのDown
	static bool GetRStickPressRight();		//RStickのRight
	static bool GetRStickPressLeft();		//RStickのLeft

public:
	static bool GetLStickTriggerUp();		//LStickのUp
	static bool GetLStickTriggerDown();		//LStickのDown
	static bool GetLStickTriggerRight();	//LStickのRight
	static bool GetLStickTriggerLeft();		//LStickのLeft
	static bool GetRStickTriggerUp();		//RStickのUp
	static bool GetRStickTriggerDown();		//RStickのDown
	static bool GetRStickTriggerRight();	//RStickのRight
	static bool GetRStickTriggerLeft();		//RStickのLeft

public:
	static bool GetLStickReleaseUp();		//LStickのUp
	static bool GetLStickReleaseDown();		//LStickのDown
	static bool GetLStickReleaseRight();	//LStickのRight
	static bool GetLStickReleaseLeft();		//LStickのLeft
	static bool GetRStickReleaseUp();		//RStickのUp
	static bool GetRStickReleaseDown();		//RStickのDown
	static bool GetRStickReleaseRight();	//RStickのRight
	static bool GetRStickReleaseLeft();		//RStickのLeft

public:
	//ButtonPress
	static bool GetButtonPressA();			//Aボタンを取得する
	static bool GetButtonPressB();			//Bボタンを取得する
	static bool GetButtonPressX();			//Xボタンを取得する
	static bool GetButtonPressY();			//Yボタンを取得する
	static bool GetButtonPressLeft();		//LEFTボタンを取得する
	static bool GetButtonPressRight();		//RIGHTボタンを取得する
	static bool GetButtonPressUp();			//UPボタンを取得する
	static bool GetButtonPressDown();		//DOWNボタンを取得する
	static bool GetButtonPressStart();		//STARTボタンを取得する
	static bool GetButtonPressBack();		//BACKボタンを取得する
	static bool GetButtonPressLThumb();		//LTHUMB(Lstick<押し込み>)ボタンを取得する
	static bool GetButtonPressRThumb();		//RTHUMB(Rstick<押し込み>)ボタンを取得する
	static bool GetButtonPressLShoulder();	//LSHOULDERボタンを取得する
	static bool GetButtonPressRShoulder();	//RSHOULDERボタンを取得する

public:
	//ButtonTrigger
	static bool GetButtonTriggerA();		//Aボタンを取得する
	static bool GetButtonTriggerB();		//Bボタンを取得する
	static bool GetButtonTriggerX();		//Xボタンを取得する
	static bool GetButtonTriggerY();		//Yボタンを取得する
	static bool GetButtonTriggerLeft();		//LEFTボタンを取得する
	static bool GetButtonTriggerRight();	//RIGHTボタンを取得する
	static bool GetButtonTriggerUp();		//UPボタンを取得する
	static bool GetButtonTriggerDown();		//DOWNボタンを取得する
	static bool GetButtonTriggerStart();	//STARTボタンを取得する
	static bool GetButtonTriggerBack();		//BACKボタンを取得する
	static bool GetButtonTriggerLThumb();	//LTHUMB(Lstick<押し込み>)ボタンを取得する
	static bool GetButtonTriggerRThumb();	//RTHUMB(Rstick<押し込み>)ボタンを取得する
	static bool GetButtonTriggerLShoulder();//LSHOULDERボタンを取得する
	static bool GetButtonTriggerRShoulder();//RSHOULDERボタンを取得する

public:
	//ButtonRelease
	static bool GetButtonReleaseA();		//Aボタンを取得する
	static bool GetButtonReleaseB();		//Bボタンを取得する
	static bool GetButtonReleaseX();		//Xボタンを取得する
	static bool GetButtonReleaseY();		//Yボタンを取得する
	static bool GetButtonReleaseLeft();		//LEFTボタンを取得する
	static bool GetButtonReleaseRight();	//RIGHTボタンを取得する
	static bool GetButtonReleaseUp();		//UPボタンを取得する
	static bool GetButtonReleaseDown();		//DOWNボタンを取得する
	static bool GetButtonReleaseStart();	//STARTボタンを取得する
	static bool GetButtonReleaseBack();		//BACKボタンを取得する
	static bool GetButtonReleaseLThumb();	//LTHUMB(Lstick<押し込み>)ボタンを取得する
	static bool GetButtonReleaseRThumb();	//RTHUMB(Rstick<押し込み>)ボタンを取得する
	static bool GetButtonReleaseLShoulder();//LSHOULDERボタンを取得する
	static bool GetButtonReleaseRShoulder();//RSHOULDERボタンを取得する

public:
	// 背面トリガー
	static float	GetLTValue();	// L側の値を正規化して返す
	static float	GetRTValue();	// R側の値を正規化して返す
	static bool		GetLTPress();	// L側が押されている時
	static bool		GetRTPress();	// R側が押されている時
	static bool		GetLTTrigger();	// L側が初めて押されたとき
	static bool		GetRTTrigger();	// R側が初めて押されたとき
	static bool		GetLTRelease();	// L側が離された時
	static bool		GetRTRelease();	// R側が離された時

private:
	static math::Float2 GetStick(const SHORT& stick_x, const SHORT& stick_y);
	static bool StickTriggerUp		(const SHORT& stick_y, const SHORT& old_stick_y);
	static bool StickTriggerDown	(const SHORT& stick_y, const SHORT& old_stick_y);
	static bool StickTriggerRight	(const SHORT& stick_x, const SHORT& old_stick_x);
	static bool StickTriggerLeft	(const SHORT& stick_x, const SHORT& old_stick_x);
	static bool StickPressUp		(const SHORT& stick_y);
	static bool StickPressDown		(const SHORT& stick_y);
	static bool StickPressRight		(const SHORT& stick_x);
	static bool StickPressLeft		(const SHORT& stick_x);
	static bool StickReleaseUp		(const SHORT& stick_y, const SHORT& old_stick_y);
	static bool StickReleaseDown	(const SHORT& stick_y, const SHORT& old_stick_y);
	static bool StickReleaseRight	(const SHORT& stick_x, const SHORT& old_stick_x);
	static bool StickReleaseLeft	(const SHORT& stick_x, const SHORT& old_stick_x);
	static bool TriggerPress		(const SHORT& trigger);
	static bool TriggerTrigger		(const SHORT& trigger, const SHORT& old_trigger);
	static bool TriggerRelease		(const SHORT& trigger, const SHORT& old_trigger);
	static bool ButtonPress			(UINT button);
	static bool ButtonTrigger		(UINT button);
	static bool ButtonRelease		(UINT button);
};	

#endif // !Controller_H_
