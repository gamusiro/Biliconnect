/*=========================================================================
	Date : 2021/12/25(�y)	TextureManager.h
		Author : ���ނ��邧
		Update :
=========================================================================*/
#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include "main.h"

#define MAX_TEXTURE_NUM	100
#define MAX_TEXTURE_ALPHABET 26

class GraphicsManager;

class TextureManager
{
public:
	static bool Init(GraphicsManager* gm);
	static void Uninit();
	/********************************************************************************
		@ brief �e�N�X�`���f�[�^�̓ǂݍ��ݏ���
		@ param
			fileName	: �e�N�X�`���̃t�@�C����
	********************************************************************************/
	static int  Load(const char* fileName);

	/********************************************************************************
		@ brief �e�N�X�`���f�[�^�̉������
		@ comment
			�ǂݍ��܂�Ă���f�[�^��S�ĊJ������
			���V�[�����ƂɃe�N�X�`���f�[�^��j�����邱�ƂŁA�p�t�H�[�}���X����ɂȂ���?
	********************************************************************************/
	static void Unload();

	/********************************************************************************
		@ brief �e�N�X�`���f�[�^�̎擾����
		@ param 
			index	: �e�N�X�`���̊Ǘ��ԍ�
		@ return 
			�e�N�X�`�����\�[�X�f�[�^
	********************************************************************************/
	static ID3D11ShaderResourceView** GetTexture(int index);

	static ID3D11ShaderResourceView** GetMask();

private:
	static GraphicsManager*			 m_GraphicsManager;
	static ID3D11ShaderResourceView* m_TextureArray[MAX_TEXTURE_NUM];
	static ID3D11ShaderResourceView* m_TextureMask;
	static char						 m_TextureName[MAX_TEXTURE_NUM][256];
	static int						 m_Index;
};

#endif // !TEXTUREMANAGER_H_



