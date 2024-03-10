/*=========================================================================
	Date : 2021/12/18(�y)	SoundManager.cpp
		Author : ���ނ��邧
		Update : 2021/12/18(��)
=========================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "GameCreateSystem.h"

#include "SoundManager.h"

IXAudio2*				SoundManager::m_XA2						= nullptr;
IXAudio2MasteringVoice* SoundManager::m_XA2MV					= nullptr;
IXAudio2SourceVoice*	SoundManager::m_XA2SV[MAX_SOUND_NUM]	= {};
IXAudio2SubmixVoice*	SoundManager::m_XA2SubV[MAX_SOUND_NUM]	= {};
BYTE*					SoundManager::m_AudioData[MAX_SOUND_NUM];
DWORD					SoundManager::m_AudioSize[MAX_SOUND_NUM];
DWORD					SoundManager::m_AudioIndex = 0;

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* chunkSize, DWORD* ChunkPosition);
HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD bufferSize, DWORD offset);

/*=============================================================================================
	����������
=============================================================================================*/
bool SoundManager::Init()
{
	//XAudio2�I�u�W�F�N�g�̐���
	XAudio2Create(&m_XA2, 0);
	if (!m_XA2)
	{//�����Ɏ��s
		std::cout << "�}�X�^�[�{�b�N�X�̐����Ɏ��s�I" << std::endl;
		return false;
	}

	//�}�X�^�[�{�C�X�̐���
	m_XA2->CreateMasteringVoice(&m_XA2MV, SOUNDMANAGER_INOUTPUT_CAHNNELS, SOUNDMANAGER_SAMPLING_RATE);
	if (!m_XA2MV)
	{
		std::cout << "�}�X�^�[�{�C�X�̐����Ɏ��s�I" << std::endl;

		if (m_XA2 != nullptr)
		{
			//XAudio2�̃I�u�W�F�N�g���
			m_XA2->Release();
			m_XA2 = nullptr;
		}

		return false;
	}
	return true;
}

/*=============================================================================================
	�I������
=============================================================================================*/
void SoundManager::Uninit()
{
	Unload();

	//�}�X�^�[�{�C�X�̔j��
	m_XA2MV->DestroyVoice();
	m_XA2MV = nullptr;

	if (m_XA2 != nullptr)
	{
		//XAudio2�I�u�W�F�N�g�̉��
		m_XA2->Release();
		m_XA2 = nullptr;
	}
}

/*=============================================================================================
	�ǂݍ��ݏ���
=============================================================================================*/
int SoundManager::Load(const char* folderPath, const char* fileName)
{
	HANDLE					hFile;
	DWORD					dwChunkSize		= 0;
	DWORD					dwChunkPosition = 0;
	DWORD					dwFiletype;
	WAVEFORMATEXTENSIBLE	wfx;
	XAUDIO2_BUFFER			buffer;

	if (m_AudioIndex == MAX_SOUND_NUM)
	{
		MessageBox(nullptr, "�ǂݍ��ݍő吔�𒴂��Ă��܂�", "OverLoads of SoundData", MB_OK | MB_ICONWARNING);
		return -1;
	}

	//�o�b�t�@�̃N���A
	::memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	::memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	//�t�@�C���p�X�̐���
	char path[256] ="";
	strcat_s(path, folderPath);
	strcat_s(path, fileName);

	hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(nullptr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "Failed Create Sound Data", MB_OK | MB_ICONWARNING);
		return -1;
	}
	if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		//�t�@�C���|�C���^��擪�Ɉړ�
		MessageBox(nullptr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "Failed Create Sound Data", MB_OK | MB_ICONWARNING);
		return -1;
	}

	HRESULT ret;

	//WAVE�t�@�C���̃`�F�b�N
	ret = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "Failed Check Wave File", MB_OK | MB_ICONWARNING);
		return -1;
	}
	ret = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "Failed Check Wave File", MB_OK | MB_ICONWARNING);
		return -1;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(nullptr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "Failed Check Wave File", MB_OK | MB_ICONWARNING);
		return -1;
	}

	//�t�H�[�}�b�g�̃`�F�b�N
	ret = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "�t�H�[�}�b�g�̃`�F�b�N�Ɏ��s�I(1)", "Failed Check Format", MB_OK | MB_ICONWARNING);
		return -1;
	}
	ret = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "�t�H�[�}�b�g�̃`�F�b�N�Ɏ��s�I(2)", "Failed Check Format", MB_OK | MB_ICONWARNING);
		return -1;
	}

	//�I�[�f�B�I�f�[�^�̓ǂݍ���
	ret = CheckChunk(hFile, 'atad', &m_AudioSize[m_AudioIndex], &dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "�I�[�f�B�I�f�[�^�̓ǂݍ��݂Ɏ��s�I(1)", "Failed Load Audio Data", MB_OK | MB_ICONWARNING);
		return -1;
	}
	m_AudioData[m_AudioIndex] = (BYTE*)malloc(m_AudioSize[m_AudioIndex]);
	ret = ReadChunkData(hFile, m_AudioData[m_AudioIndex], m_AudioSize[m_AudioIndex], dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "�I�[�f�B�I�f�[�^�̓ǂݍ��݂Ɏ��s�I(2)", "Failed Load Audio Data", MB_OK | MB_ICONWARNING);
		return -1;
	}

	//�\�[�X�{�C�X�̐���
	ret = m_XA2->CreateSourceVoice(&m_XA2SV[m_AudioIndex], &(wfx.Format), XAUDIO2_VOICE_USEFILTER);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "�\�[�X�{�C�X�̐����Ɏ��s�I(2)", "Failed Create Source Voice", MB_OK | MB_ICONWARNING);
		return -1;
	}

	// �T�u�~�b�N�X�{�C�X�̍쐬
	ret = m_XA2->CreateSubmixVoice(&m_XA2SubV[m_AudioIndex], SOUNDMANAGER_INOUTPUT_CAHNNELS, SOUNDMANAGER_SAMPLING_RATE);
	if (m_XA2SubV[m_AudioIndex])
	{
		XAUDIO2_SEND_DESCRIPTOR send{ 0, m_XA2SubV[m_AudioIndex] };
		XAUDIO2_VOICE_SENDS		sendList{ 1, &send };
		m_XA2SV[m_AudioIndex]->SetOutputVoices(&sendList);
	}
	
	int retIndex = m_AudioIndex;
	m_AudioIndex++;

	return retIndex;
}

/*=============================================================================================
	�ǂݍ��񂾃f�[�^�̉������
=============================================================================================*/
void SoundManager::Unload()
{
	for (unsigned int i = 0; i < m_AudioIndex; i++)
	{
		//�ꎞ��~
		m_XA2SV[i]->Stop(0);

		m_XA2SubV[i]->DestroyVoice();
		m_XA2SubV[i] = nullptr;

		//�\�[�X�f�[�^�̔j��
		m_XA2SV[i]->DestroyVoice();
		m_XA2SV[i] = nullptr;

		//�I�[�f�B�I�f�[�^�̉��
		free(m_AudioData[i]);
		m_AudioData[i] = nullptr;
	}
	m_AudioIndex = 0;
}

/*=============================================================================================
	�ǂݍ��ݏ���
=============================================================================================*/
void SoundManager::Play(int index, int loopCnt)
{
	XAUDIO2_VOICE_STATE xa2state = {};
	XAUDIO2_BUFFER		buffer = {};

	//�o�b�t�@�̒l�ݒ�
	::memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_AudioSize[index];
	buffer.pAudioData = m_AudioData[index];
	buffer.Flags = XAUDIO2_END_OF_STREAM;

	//0�������w�肷��ꍇ
	if (loopCnt < 0)
	{
		//�������[�v
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else
	{
		buffer.LoopCount = loopCnt;
	}

	if (m_XA2SV[index])
	{
		m_XA2SV[index]->Stop();
		m_XA2SV[index]->FlushSourceBuffers();
	}

	//�I�[�f�B�I�o�b�t�@�̓o�^
	m_XA2SV[index]->SubmitSourceBuffer(&buffer);

	//�Đ�
	m_XA2SV[index]->Start(0);
}

/*=============================================================================================
	�ꎞ��~����
=============================================================================================*/
void SoundManager::Pause(int index)
{
	m_XA2SV[index]->Stop(XAUDIO2_PLAY_TAILS);
}

/*=============================================================================================
	��~����
=============================================================================================*/
void SoundManager::Stop(int index)
{
	XAUDIO2_VOICE_STATE xa2state;

	//��Ԃ̎擾
	m_XA2SV[index]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{
		//�ꎞ��~
		m_XA2SV[index]->Stop(0);
		//�I�[�f�B�I�o�b�t�@�̍폜
		m_XA2SV[index]->FlushSourceBuffers();
	}
}

/*=============================================================================================
	���ʒ��ߏ���
=============================================================================================*/
void SoundManager::SetVolume(int index, int value)
{
	float volume = 0.0f;

	//�͈͂�0�`100�܂�
	value = max(0, value);
	value = min(value, 100);

	//0.0f�`1.0f�ɕϊ�����
	volume = 1.0f * (value * 0.01f);

	m_XA2SV[index]->SetVolume(volume);
}

/*=============================================================================================
	�p���j���O���ߏ���
=============================================================================================*/
void SoundManager::SetPanning(int index, int left, int right, float degree)
{
	UINT inChannel, outChannel;
	XAUDIO2_VOICE_DETAILS vd = {};
	m_XA2SV[index]->GetVoiceDetails(&vd);
	inChannel = vd.InputChannels;

	m_XA2MV->GetVoiceDetails(&vd);
	outChannel = vd.InputChannels;

	if (outChannel == 2)
	{//5.1ch�@��łȂ���ΐݒ�s��
		float Lvolume = 0.0f;
		float Rvolume = 0.0f;

		left = math::MathCommons::Max(0, left);
		left = math::MathCommons::Min(left, 100);

		right = math::MathCommons::Max(0, right);
		right = math::MathCommons::Min(right, 100);

		float radian = math::MathCommons::Radian(degree);
		float volumes[6] = {};
		volumes[0] = (1.0f / 100 * left) * cosf(radian);
		volumes[3] = (1.0f / 100 * right) * sinf(radian);
		m_XA2SV[index]->SetOutputMatrix(nullptr, inChannel, outChannel, volumes);
	}
}

/*=============================================================================================
	���o�[�u�̐ݒ菈��
=============================================================================================*/
void SoundManager::SetReverb(int index, const char* fileName)
{
	if (m_XA2SubV[index])
	{
		HRESULT		ret = S_OK;
		IUnknown* pXAPO = nullptr;
		ret = XAudio2CreateReverb(&pXAPO);
		if (FAILED(ret) || !pXAPO)
		{
			return;
		}

		// �ŃX�N���v�^�[
		XAUDIO2_EFFECT_DESCRIPTOR descriptor{};
		descriptor.InitialState = true;
		descriptor.OutputChannels = SOUNDMANAGER_INOUTPUT_CAHNNELS;
		descriptor.pEffect = pXAPO;

		// �`�F�C���̐�������
		XAUDIO2_EFFECT_CHAIN effectChain{};
		effectChain.EffectCount = 1;
		effectChain.pEffectDescriptors = &descriptor;

		// �~�b�N�X�{�C�X�ɐݒ肷��
		m_XA2SubV[index]->SetEffectChain(&effectChain);
		if (pXAPO) pXAPO->Release();
	}

	// rvb�t�@�C���̓ǂݍ��ݏ���
	FILE* pFile{ nullptr };
	pFile = std::fopen(fileName, "r");
	if (!pFile)
	{
		return;
	}
	XAUDIO2FX_REVERB_PARAMETERS params{};
	std::fread(&params.WetDryMix,			sizeof(float), 1, pFile);
	std::fread(&params.ReflectionsDelay,	sizeof(UINT32), 1, pFile);
	std::fread(&params.ReverbDelay,			sizeof(BYTE), 1, pFile);
	std::fread(&params.RearDelay,			sizeof(BYTE), 1, pFile);
	std::fseek(pFile, 1, SEEK_CUR);
	std::fread(&params.PositionLeft,		sizeof(BYTE), 1, pFile);
	std::fread(&params.PositionRight,		sizeof(BYTE), 1, pFile);
	std::fread(&params.PositionMatrixLeft,	sizeof(BYTE), 1, pFile);
	std::fread(&params.PositionMatrixRight,	sizeof(BYTE), 1, pFile);
	std::fread(&params.EarlyDiffusion,		sizeof(BYTE), 1, pFile);
	std::fread(&params.LateDiffusion,		sizeof(BYTE), 1, pFile);
	std::fread(&params.LowEQGain,			sizeof(BYTE), 1, pFile);
	std::fread(&params.LowEQCutoff,			sizeof(BYTE), 1, pFile);
	std::fread(&params.HighEQGain,			sizeof(BYTE), 1, pFile);
	std::fread(&params.HighEQCutoff,		sizeof(BYTE), 1, pFile);
	std::fread(&params.RoomFilterFreq,		sizeof(float), 1, pFile);
	std::fread(&params.RoomFilterMain,		sizeof(float), 1, pFile);
	std::fread(&params.RoomFilterHF,		sizeof(float), 1, pFile);
	std::fread(&params.ReflectionsGain,		sizeof(float), 1, pFile);
	std::fread(&params.ReverbGain,			sizeof(float), 1, pFile);
	std::fread(&params.DecayTime,			sizeof(float), 1, pFile);
	std::fread(&params.Density,				sizeof(float), 1, pFile);
	std::fread(&params.RoomSize,			sizeof(float), 1, pFile);
	std::fclose(pFile);

	// ���o�[�u�̐ݒ菈��
	m_XA2SubV[index]->SetEffectParameters(0, &params, sizeof(XAUDIO2FX_REVERB_PARAMETERS));
}

/*=============================================================================================
	WAVE�t�H�[�}�b�g�̃`�F�b�N
=============================================================================================*/
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* chunkSize, DWORD* chunkPosition)
{
	HRESULT ret = S_OK;
	DWORD	dwRead			= 0;
	DWORD	dwChunkType		= 0;
	DWORD	dwChunkDataSize = 0;
	DWORD	dwRIFFDataSize	= 0;
	DWORD	dwFileType		= 0;
	DWORD	dwBytesRead		= 0;
	DWORD	offset			= 0;

	if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		//�t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (ret == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, nullptr) == 0)
		{
			//�`�����N�̓ǂݍ���
			ret = HRESULT_FROM_WIN32(GetLastError());
		}
		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, nullptr) == 0)
		{
			//�`�����N�f�[�^�̓ǂݍ���
			ret = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, nullptr) == 0)
			{
				//�t�@�C���^�C�v�̓ǂݍ���
				ret = HRESULT_FROM_WIN32(GetLastError());
			}
			break;
		default:
			if (SetFilePointer(hFile, dwChunkDataSize, nullptr, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{
				//�t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		offset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*chunkSize		= dwChunkDataSize;
			*chunkPosition	= offset;

			return S_OK;
		}

		offset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	return S_OK;
}

/*=============================================================================================
	WAVE�t�H�[�}�b�g�̓ǂݍ���
=============================================================================================*/
HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD bufferSize, DWORD offset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, offset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		//�t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, buffer, bufferSize, &dwRead, nullptr) == 0)
	{
		//�t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
