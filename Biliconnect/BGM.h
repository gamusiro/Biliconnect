/*=========================================================================
	Date : 2021/12/19(��)	BGM.h
		Author : ���ނ��邧
		Update : 2021/12/19(��)
=========================================================================*/
#ifndef BGM_H_
#define BGM_H_

#include "SoundInterface.h"

class BGM : public SoundInterface
{
public:
	BGM();
	~BGM();

public:
	/*
	* @ brief
	*		���y�f�[�^�����[�h����
	* @ param 
	*		fileName : �t�@�C���̖��O
	* @ comment
	*		������Material/Sound/BGM/fileName�̃p�X�ɕϊ������
	*/
	void Load(const char* fileName) override;

	/*
	* @ brief
	*		���y�f�[�^���Đ�����
	* @ param
	*		loopCount : ���[�v��
	*/
	void Play(int loopCount = -1) override;

	/*
	* @ brief
	*		���y�f�[�^���ꎞ��~����
	*/
	void Pause() override;

	/*
	* @ brief
	*		���y�f�[�^���~����
	*/
	void Stop() override;

	/*
	* @ brief
	*		���y�f�[�^�̉��ʐݒ�
	* @ param
	*		volume : ���ʂ̐ݒ�(0 ~ 100)
	*/
	void SetVolume(int volume) override;

	/*
	* @ brief
	*		�o�̓f�o�C�X�̂̉��ʐݒ�
	* @ param
	*		left  : ���ʂ̐ݒ�(0 ~ 100)
	*		right : ���ʂ̐ݒ�(0 ~ 100)
	*		degree: �p�x
	* @ comment
	*		�Ή��X�^�C����5.1ch�̂�
	*/
	void SetPanning(int left, int right, float degree = 45.0f) override;
};

#endif // !BGM_H_



