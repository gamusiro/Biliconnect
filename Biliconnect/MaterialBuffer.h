/*===========================================================================
	Date : 2022/02/11(��)	MaterialBuffer.h
		Author	: ���ނ��邧
		Update	:
		Comment	: ���񗘗p�������̂̓e�N�X�`���𗘗p���邩�A
				�@�|���S����`�悷�邩�̓���Ȃ̂� bool�ł悢�̂����A
				  �o�b�t�@�̓s����16�o�C�g�͍Œ�ł��K�v�炵���̂ŁA
				  �K���ȍ\���̂�����Ă��܂��܂��傤�Ƃ�����ł��B
===========================================================================*/
#ifndef MATERIALBUFFER_H_
#define MATERIALBUFFER_H_

#include "main.h"

//�\���̂�16�̔{���łȂ���΂Ȃ�Ȃ�
struct Material
{
	int		noTexSampling;	//�e�N�X�`���̗��p�t���O(1: ���p����, 0: ���p���Ȃ�)
	float	Dummy[3];		//16byte���E�p
};

class GraphicsManager;

class MaterialBuffer
{
public:
	static bool Init(GraphicsManager* gm);		//����������
	static void SetData(const Material& data);	//�f�[�^�̐ݒ菈��
	static void Uninit();						//�I������

private:
	static GraphicsManager*	m_GraphicsManager;
	static ID3D11Buffer*	m_MaterialBuffer;
};

#endif // !MATERIALBUFFER_H_
