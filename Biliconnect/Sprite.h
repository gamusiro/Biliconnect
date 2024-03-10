/*===========================================================================
	Date : 2022/02/08(��)	Sprite.h
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#ifndef SPRITE_H_
#define SPRITE_H_

#include "main.h"

class GraphicsManager;
class Texture;

class Sprite
{
public:
	static bool Init(GraphicsManager* gm);
	static void Uninit();
	/*
	*	@ brief
	*		�����̋�`�̕`��
	*	@ param
	*		pos		: ���㒸�_���W
	*		_size	: ��`�̃T�C�Y
	*		color	: �J���[
	*/
	static void DrawLeftTop(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = {1, 1, 1, 1});

	/*
	*	@ brief
	*		���S��̋�`�̕`��
	*	@ param
	*		pos		: ���S���W
	*		_size	: ��`�̃T�C�Y
	*		color	: �J���[
	*/
	static void DrawCenter(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = {1, 1, 1, 1},
		float degree = 0.0f);

	static void DrawBottom(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = { 1, 1, 1, 1 },
		float degree = 0.0f);

	static void DrawCenterK(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = { 1, 1, 1, 1 },
		float degree = 0.0f);

	/*
	*	@ brief
	*		�}�X�N�p
	*	@ param
	*		pos		: ���S���W
	*		_size	: ��`�̃T�C�Y
	*		color	: �J���[
	* @ comment	
	*		�V�[�����܂����`��̏ꍇ��Texture�N���X�̃����o�֐� Create(�Ńt�@�C����ǂݍ���ł͂����Ȃ�) ���p�s�B
	*		(��)�e�N�X�`���̃A�j���[�V����������ꍇ��Create�̎g�p�@:
	*				texture->Create(nullptr, 2, 2, 10);
	*				texture->SetImageID(0);
	* 
	*		�}�X�N�摜�̊Ǘ����@�͌������E�E�E
	*/
	static void DrawMask(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = { 1, 1, 1, 1 },
		float degree = 0.0f);

private:
	static GraphicsManager* m_GraphicsManager;
	static ID3D11Buffer*	m_VertexBuffer;
};

#endif // !SPRITE_H_
