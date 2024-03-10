#pragma once

class Volume
{
private:
	static int m_VolumeSE;
	static int m_VolumeBGM;

public:
	static void	SetSE(int volume) { m_VolumeSE = volume; };
	static int	GetSE(void) { return m_VolumeSE; }
	static void	SetBGM(int volume) { m_VolumeBGM = volume; };
	static int	GetBGM(void) { return m_VolumeBGM; }
};
__declspec(selectany) int Volume::m_VolumeSE(3);
__declspec(selectany) int Volume::m_VolumeBGM(3);