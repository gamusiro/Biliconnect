/*=========================================================================
	Date : 2022/05/30(��)	Opening.h
		Author : ���ނ��邧
		Update :
=========================================================================*/
#ifndef OPENING_H_
#define OPENING_H_

#include "GameCreateSystem.h"
#include "SceneInterface.h"

class Opening : public SceneInterface
{
public:
	void Init();	//����������
	void Uninit();	//�I������
	void Update();	//�X�V����
	void Draw();	//�`�揈��
};

#endif // !OPENING_H_