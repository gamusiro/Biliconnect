/*=========================================================================
	Date : 2021/12/19(“ú)	SoundInterface.h
		Author : ‚ª‚Þ‚µ‚é‚§
		Update : 2021/12/19(“ú)
=========================================================================*/
#ifndef SOUNDINTERFACE_H_
#define SOUNDINTERFACE_H_

class SoundInterface
{
public:
	SoundInterface() : m_soundID(-1) {}

public:
	virtual void Load(const char* fileName) = 0;
	virtual void Play(int loopCount = -1) = 0;
	virtual void Pause() = 0;
	virtual void Stop() = 0;
	virtual void SetVolume(int volume) = 0;
	virtual void SetPanning(int left, int right, float degree) = 0;

protected:
	int m_soundID;
};

#endif // !SOUNDINTERFACE_H_

