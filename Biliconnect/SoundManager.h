/*=========================================================================
	Date : 2021/12/18(�y)	SoundManager.h
		Author : ���ނ��邧
		Update : 2021/12/19(��)
=========================================================================*/
#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <Windows.h>
#include "XAudio2.h"
#include <xaudio2fx.h>

#pragma comment(lib, "xaudio2.lib")

#define SOUNDMANAGER_INOUTPUT_CAHNNELS	2
#define SOUNDMANAGER_SAMPLING_RATE		44100

#define MAX_SOUND_NUM	100

class SoundManager
{
public:
	static bool Init();		//����������
	static void Unload();	//�S�������
	static void Uninit();	//�I������

private:
	//�����o�֐�
	static int  Load(const char* folderName, const char* fileName);			//�ǂݍ��ݏ���
	static void Play(int index, int loopCnt);								//�Đ�����
	static void Pause(int index);											//�ꎞ��~����
	static void Stop(int index);											//��~����
	static void SetVolume(int index, int value);							//���ʒ��ߏ���
	static void SetPanning(int index, int left, int right, float degree);	//�p���j���O�̐ݒ菈��
	static void SetReverb(int index, const char* fileName);					//���o�[�u�̐ݒ菈��

private:
	static IXAudio2*				m_XA2;
	static IXAudio2MasteringVoice*	m_XA2MV;
	static IXAudio2SourceVoice*		m_XA2SV[MAX_SOUND_NUM];
	static IXAudio2SubmixVoice*		m_XA2SubV[MAX_SOUND_NUM];
	static BYTE*					m_AudioData[MAX_SOUND_NUM];
	static DWORD					m_AudioSize[MAX_SOUND_NUM];
	static DWORD					m_AudioIndex;

private:
	friend class BGM;
	friend class SE;
};

#endif // !SOUNDMANAGER_H_



