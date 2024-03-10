/*===========================================================================
	Date : 2022/02/08(��)	SamplerState.h
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#ifndef SAMPLERSTATE_H_
#define SAMPLERSTATE_H_

#include "main.h"

class GraphicsManager;

/**********************************************************
	@brief �A�h���X���[�h�̎w��
	WRAP	: �e�N�X�`�����J��Ԃ�(�����͓���)
	MIRROR	: �e�N�X�`�����~���[�����O����(���������]����)
	CLAMP	: �e�N�X�`�����N�����v����
	BORDER	: �e�N�X�`�����{�[�_�[����(���E���̐F���K�p�����)
**********************************************************/
enum class ADDRESS_MODE
{
	WRAP,
	MIRROR,
	CLAMP,
	BORDER
};

/**********************************************************
	@brief �t�B���^�[���[�h�̎w��
	POINT		: �|�C���g�t�B���^�����O(��掿�A��R�X�g)
	LINEAR		: �o�C���j�A�t�B���^�����O(2����)
	ANISOTOROPIC: �A�j�\�g���s�b�N�t�B���^�����O(���掿�A���R�X�g)
**********************************************************/
enum class FILTER_MODE
{
	POINT,
	LINEAR,
	ANISOTROPIC
};

class SamplerState
{
public:
	SamplerState(GraphicsManager* gm);
	~SamplerState();

public:
	bool Create();									//��������
	void SetMode(ADDRESS_MODE am, FILTER_MODE fm);	//���[�h�ݒ菈��
	void SetColor(math::Float4 boaderColor);		//�{�[�_�[�J���[�̎w��				
	void Release();									//�������

private:
	GraphicsManager*	m_GraphicsManager;
	math::Float4		m_BorderColor;
};

#endif // !SAMPLERSTATE_H_
