/*=========================================================================
	Date : 2021/12/18(土)	SoundManager.cpp
		Author : がむしるぉ
		Update : 2021/12/18(日)
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
	初期化処理
=============================================================================================*/
bool SoundManager::Init()
{
	//XAudio2オブジェクトの生成
	XAudio2Create(&m_XA2, 0);
	if (!m_XA2)
	{//生成に失敗
		std::cout << "マスターボックスの生成に失敗！" << std::endl;
		return false;
	}

	//マスターボイスの生成
	m_XA2->CreateMasteringVoice(&m_XA2MV, SOUNDMANAGER_INOUTPUT_CAHNNELS, SOUNDMANAGER_SAMPLING_RATE);
	if (!m_XA2MV)
	{
		std::cout << "マスターボイスの生成に失敗！" << std::endl;

		if (m_XA2 != nullptr)
		{
			//XAudio2のオブジェクト解放
			m_XA2->Release();
			m_XA2 = nullptr;
		}

		return false;
	}
	return true;
}

/*=============================================================================================
	終了処理
=============================================================================================*/
void SoundManager::Uninit()
{
	Unload();

	//マスターボイスの破棄
	m_XA2MV->DestroyVoice();
	m_XA2MV = nullptr;

	if (m_XA2 != nullptr)
	{
		//XAudio2オブジェクトの解放
		m_XA2->Release();
		m_XA2 = nullptr;
	}
}

/*=============================================================================================
	読み込み処理
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
		MessageBox(nullptr, "読み込み最大数を超えています", "OverLoads of SoundData", MB_OK | MB_ICONWARNING);
		return -1;
	}

	//バッファのクリア
	::memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	::memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	//ファイルパスの生成
	char path[256] ="";
	strcat_s(path, folderPath);
	strcat_s(path, fileName);

	hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(nullptr, "サウンドデータファイルの生成に失敗！(1)", "Failed Create Sound Data", MB_OK | MB_ICONWARNING);
		return -1;
	}
	if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		//ファイルポインタを先頭に移動
		MessageBox(nullptr, "サウンドデータファイルの生成に失敗！(2)", "Failed Create Sound Data", MB_OK | MB_ICONWARNING);
		return -1;
	}

	HRESULT ret;

	//WAVEファイルのチェック
	ret = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "WAVEファイルのチェックに失敗！(1)", "Failed Check Wave File", MB_OK | MB_ICONWARNING);
		return -1;
	}
	ret = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "WAVEファイルのチェックに失敗！(2)", "Failed Check Wave File", MB_OK | MB_ICONWARNING);
		return -1;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(nullptr, "WAVEファイルのチェックに失敗！(3)", "Failed Check Wave File", MB_OK | MB_ICONWARNING);
		return -1;
	}

	//フォーマットのチェック
	ret = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "フォーマットのチェックに失敗！(1)", "Failed Check Format", MB_OK | MB_ICONWARNING);
		return -1;
	}
	ret = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "フォーマットのチェックに失敗！(2)", "Failed Check Format", MB_OK | MB_ICONWARNING);
		return -1;
	}

	//オーディオデータの読み込み
	ret = CheckChunk(hFile, 'atad', &m_AudioSize[m_AudioIndex], &dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "オーディオデータの読み込みに失敗！(1)", "Failed Load Audio Data", MB_OK | MB_ICONWARNING);
		return -1;
	}
	m_AudioData[m_AudioIndex] = (BYTE*)malloc(m_AudioSize[m_AudioIndex]);
	ret = ReadChunkData(hFile, m_AudioData[m_AudioIndex], m_AudioSize[m_AudioIndex], dwChunkPosition);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "オーディオデータの読み込みに失敗！(2)", "Failed Load Audio Data", MB_OK | MB_ICONWARNING);
		return -1;
	}

	//ソースボイスの生成
	ret = m_XA2->CreateSourceVoice(&m_XA2SV[m_AudioIndex], &(wfx.Format), XAUDIO2_VOICE_USEFILTER);
	if (FAILED(ret))
	{
		MessageBox(nullptr, "ソースボイスの生成に失敗！(2)", "Failed Create Source Voice", MB_OK | MB_ICONWARNING);
		return -1;
	}

	// サブミックスボイスの作成
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
	読み込んだデータの解放処理
=============================================================================================*/
void SoundManager::Unload()
{
	for (unsigned int i = 0; i < m_AudioIndex; i++)
	{
		//一時停止
		m_XA2SV[i]->Stop(0);

		m_XA2SubV[i]->DestroyVoice();
		m_XA2SubV[i] = nullptr;

		//ソースデータの破棄
		m_XA2SV[i]->DestroyVoice();
		m_XA2SV[i] = nullptr;

		//オーディオデータの解放
		free(m_AudioData[i]);
		m_AudioData[i] = nullptr;
	}
	m_AudioIndex = 0;
}

/*=============================================================================================
	読み込み処理
=============================================================================================*/
void SoundManager::Play(int index, int loopCnt)
{
	XAUDIO2_VOICE_STATE xa2state = {};
	XAUDIO2_BUFFER		buffer = {};

	//バッファの値設定
	::memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_AudioSize[index];
	buffer.pAudioData = m_AudioData[index];
	buffer.Flags = XAUDIO2_END_OF_STREAM;

	//0未満を指定する場合
	if (loopCnt < 0)
	{
		//無限ループ
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

	//オーディオバッファの登録
	m_XA2SV[index]->SubmitSourceBuffer(&buffer);

	//再生
	m_XA2SV[index]->Start(0);
}

/*=============================================================================================
	一時停止処理
=============================================================================================*/
void SoundManager::Pause(int index)
{
	m_XA2SV[index]->Stop(XAUDIO2_PLAY_TAILS);
}

/*=============================================================================================
	停止処理
=============================================================================================*/
void SoundManager::Stop(int index)
{
	XAUDIO2_VOICE_STATE xa2state;

	//状態の取得
	m_XA2SV[index]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{
		//一時停止
		m_XA2SV[index]->Stop(0);
		//オーディオバッファの削除
		m_XA2SV[index]->FlushSourceBuffers();
	}
}

/*=============================================================================================
	音量調節処理
=============================================================================================*/
void SoundManager::SetVolume(int index, int value)
{
	float volume = 0.0f;

	//範囲は0～100まで
	value = max(0, value);
	value = min(value, 100);

	//0.0f～1.0fに変換する
	volume = 1.0f * (value * 0.01f);

	m_XA2SV[index]->SetVolume(volume);
}

/*=============================================================================================
	パンニング調節処理
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
	{//5.1ch機器でなければ設定不可
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
	リバーブの設定処理
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

		// でスクリプター
		XAUDIO2_EFFECT_DESCRIPTOR descriptor{};
		descriptor.InitialState = true;
		descriptor.OutputChannels = SOUNDMANAGER_INOUTPUT_CAHNNELS;
		descriptor.pEffect = pXAPO;

		// チェインの生成処理
		XAUDIO2_EFFECT_CHAIN effectChain{};
		effectChain.EffectCount = 1;
		effectChain.pEffectDescriptors = &descriptor;

		// ミックスボイスに設定する
		m_XA2SubV[index]->SetEffectChain(&effectChain);
		if (pXAPO) pXAPO->Release();
	}

	// rvbファイルの読み込み処理
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

	// リバーブの設定処理
	m_XA2SubV[index]->SetEffectParameters(0, &params, sizeof(XAUDIO2FX_REVERB_PARAMETERS));
}

/*=============================================================================================
	WAVEフォーマットのチェック
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
		//ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (ret == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, nullptr) == 0)
		{
			//チャンクの読み込み
			ret = HRESULT_FROM_WIN32(GetLastError());
		}
		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, nullptr) == 0)
		{
			//チャンクデータの読み込み
			ret = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, nullptr) == 0)
			{
				//ファイルタイプの読み込み
				ret = HRESULT_FROM_WIN32(GetLastError());
			}
			break;
		default:
			if (SetFilePointer(hFile, dwChunkDataSize, nullptr, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{
				//ファイルポインタをチャンクデータ分移動
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
	WAVEフォーマットの読み込み
=============================================================================================*/
HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD bufferSize, DWORD offset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, offset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		//ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, buffer, bufferSize, &dwRead, nullptr) == 0)
	{
		//ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
