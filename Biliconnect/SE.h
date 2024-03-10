/*=========================================================================
	Date : 2021/12/20(��)	SE.h
		Author : ���ނ��邧
		Update : 
=========================================================================*/
#ifndef SE_H_
#define SE_H_

#include "SoundInterface.h"

class SE : public SoundInterface
{
public:
	SE();
	~SE();

public:
	/*
	* @ brief
	*		���y�f�[�^�����[�h����
	* @ param
	*		fileName : �t�@�C���̖��O
	* @ comment
	*		������Material/Sound/SE/fileName�̃p�X�ɕϊ������
	*/
	void Load(const char* fileName) override;

	/*
	* @ brief \
	*		���o�[�u�̐ݒ菈��
	* @ param \
	*		
	*/
	void SetReverb(const char* fileName);

	/*
	* @ brief
	*		���y�f�[�^���Đ�����
	* @ param
	*		loopCount : ���[�v��
	*/
	void Play(int loopCount) override;
	
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
	void SetPanning(int left, int right, float degree = 45.0f);
};

#endif // !SE_H_
