/*=============================================================================================================
	Controller.cpp (Xinput�𗘗p)
				Author	:	�� �l

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
	//Xinput�𗘗p����(main.cpp�ɏ�������)
	static void Init();		//������
	static void Uninit();	//�I������
	static void Update();	//�X�V����

public:
	//�R���g���[���[�̐U��
	static void SetVibration	 (UINT val);	//�����U��(0�`)
	static void SetVibrationRight(UINT val);	//�E���̂ݐU��
	static void SetVibrationLeft (UINT val);	//�����̂ݐU��
	static void StopVibration();				//�U���̒�~(�U����������Ă΂Ȃ��Ǝ~�܂�Ȃ���e�w�y��)

public:
	//Stick�̒l���擾
	static math::Float2 GetLeftStick();			//DeadZone��-0.1f�`0.1f�ꍇ(Float2���Ȃ��ꍇ��D3DVECTOR2���g����OK!)
	static math::Float2 GetRightStick();		//DeadZone��-0.1f�`0.1f�ꍇ(Float2���Ȃ��ꍇ��D3DVECTOR2���g����OK!)

public:
	static bool GetLStickPressUp();			//LStick��Up
	static bool GetLStickPressDown();		//LStick��Down
	static bool GetLStickPressRight();		//LStick��Right
	static bool GetLStickPressLeft();		//LStick��Left
	static bool GetRStickPressUp();			//RStick��Up
	static bool GetRStickPressDown();		//RStick��Down
	static bool GetRStickPressRight();		//RStick��Right
	static bool GetRStickPressLeft();		//RStick��Left

public:
	static bool GetLStickTriggerUp();		//LStick��Up
	static bool GetLStickTriggerDown();		//LStick��Down
	static bool GetLStickTriggerRight();	//LStick��Right
	static bool GetLStickTriggerLeft();		//LStick��Left
	static bool GetRStickTriggerUp();		//RStick��Up
	static bool GetRStickTriggerDown();		//RStick��Down
	static bool GetRStickTriggerRight();	//RStick��Right
	static bool GetRStickTriggerLeft();		//RStick��Left

public:
	static bool GetLStickReleaseUp();		//LStick��Up
	static bool GetLStickReleaseDown();		//LStick��Down
	static bool GetLStickReleaseRight();	//LStick��Right
	static bool GetLStickReleaseLeft();		//LStick��Left
	static bool GetRStickReleaseUp();		//RStick��Up
	static bool GetRStickReleaseDown();		//RStick��Down
	static bool GetRStickReleaseRight();	//RStick��Right
	static bool GetRStickReleaseLeft();		//RStick��Left

public:
	//ButtonPress
	static bool GetButtonPressA();			//A�{�^�����擾����
	static bool GetButtonPressB();			//B�{�^�����擾����
	static bool GetButtonPressX();			//X�{�^�����擾����
	static bool GetButtonPressY();			//Y�{�^�����擾����
	static bool GetButtonPressLeft();		//LEFT�{�^�����擾����
	static bool GetButtonPressRight();		//RIGHT�{�^�����擾����
	static bool GetButtonPressUp();			//UP�{�^�����擾����
	static bool GetButtonPressDown();		//DOWN�{�^�����擾����
	static bool GetButtonPressStart();		//START�{�^�����擾����
	static bool GetButtonPressBack();		//BACK�{�^�����擾����
	static bool GetButtonPressLThumb();		//LTHUMB(Lstick<��������>)�{�^�����擾����
	static bool GetButtonPressRThumb();		//RTHUMB(Rstick<��������>)�{�^�����擾����
	static bool GetButtonPressLShoulder();	//LSHOULDER�{�^�����擾����
	static bool GetButtonPressRShoulder();	//RSHOULDER�{�^�����擾����

public:
	//ButtonTrigger
	static bool GetButtonTriggerA();		//A�{�^�����擾����
	static bool GetButtonTriggerB();		//B�{�^�����擾����
	static bool GetButtonTriggerX();		//X�{�^�����擾����
	static bool GetButtonTriggerY();		//Y�{�^�����擾����
	static bool GetButtonTriggerLeft();		//LEFT�{�^�����擾����
	static bool GetButtonTriggerRight();	//RIGHT�{�^�����擾����
	static bool GetButtonTriggerUp();		//UP�{�^�����擾����
	static bool GetButtonTriggerDown();		//DOWN�{�^�����擾����
	static bool GetButtonTriggerStart();	//START�{�^�����擾����
	static bool GetButtonTriggerBack();		//BACK�{�^�����擾����
	static bool GetButtonTriggerLThumb();	//LTHUMB(Lstick<��������>)�{�^�����擾����
	static bool GetButtonTriggerRThumb();	//RTHUMB(Rstick<��������>)�{�^�����擾����
	static bool GetButtonTriggerLShoulder();//LSHOULDER�{�^�����擾����
	static bool GetButtonTriggerRShoulder();//RSHOULDER�{�^�����擾����

public:
	//ButtonRelease
	static bool GetButtonReleaseA();		//A�{�^�����擾����
	static bool GetButtonReleaseB();		//B�{�^�����擾����
	static bool GetButtonReleaseX();		//X�{�^�����擾����
	static bool GetButtonReleaseY();		//Y�{�^�����擾����
	static bool GetButtonReleaseLeft();		//LEFT�{�^�����擾����
	static bool GetButtonReleaseRight();	//RIGHT�{�^�����擾����
	static bool GetButtonReleaseUp();		//UP�{�^�����擾����
	static bool GetButtonReleaseDown();		//DOWN�{�^�����擾����
	static bool GetButtonReleaseStart();	//START�{�^�����擾����
	static bool GetButtonReleaseBack();		//BACK�{�^�����擾����
	static bool GetButtonReleaseLThumb();	//LTHUMB(Lstick<��������>)�{�^�����擾����
	static bool GetButtonReleaseRThumb();	//RTHUMB(Rstick<��������>)�{�^�����擾����
	static bool GetButtonReleaseLShoulder();//LSHOULDER�{�^�����擾����
	static bool GetButtonReleaseRShoulder();//RSHOULDER�{�^�����擾����

public:
	// �w�ʃg���K�[
	static float	GetLTValue();	// L���̒l�𐳋K�����ĕԂ�
	static float	GetRTValue();	// R���̒l�𐳋K�����ĕԂ�
	static bool		GetLTPress();	// L����������Ă��鎞
	static bool		GetRTPress();	// R����������Ă��鎞
	static bool		GetLTTrigger();	// L�������߂ĉ����ꂽ�Ƃ�
	static bool		GetRTTrigger();	// R�������߂ĉ����ꂽ�Ƃ�
	static bool		GetLTRelease();	// L���������ꂽ��
	static bool		GetRTRelease();	// R���������ꂽ��

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
