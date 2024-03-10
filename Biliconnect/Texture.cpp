/*=========================================================================
	Date : 2021/12/26(�y)	GameCreateSystem.h
		Author : ���ނ��邧
		Update :
=========================================================================*/
#include "TextureManager.h"

#include "Texture.h"
using namespace math;

/*===================================================================
	�R���X�g���N�^
===================================================================*/
Texture::Texture()
	:m_Frame(),
	m_Info(),
	m_Direction(DIRECTION_TEXTURE::LEFT)
{
}

/*===================================================================
	�f�X�g���N�^
===================================================================*/
Texture::~Texture()
{
}

/*===================================================================
	�摜�f�[�^�̐���
===================================================================*/
void Texture::Create(const char* fileName, int column, int row, int frame)
{
	//�t�@�C������nullptr�łȂ����
	if (fileName != nullptr)
		this->m_Info.TextureID = TextureManager::Load(fileName);
	else
		this->m_Info.TextureID = -1;

	//�J�b�g�T�C�Y���s�K�؂łȂ����
	if (column > 0 && row > 0)
	{
		this->m_Info.TotalTexture = column * row;
		this->m_Info.CutNum = Int2(column, row);
		this->m_Info.SizeUV = Float2(1.0f / column, 1.0f / row);
	}
	else
	{
		this->m_Info.TotalTexture = 1 * 1;
		this->m_Info.CutNum = Int2(1, 1);
		this->m_Info.SizeUV = Float2(1.0f, 1.0f);
	}

	this->m_Frame.Criteria = frame;
	
}

/*===================================================================
	�e�N�X�`���̍X�V
===================================================================*/
void Texture::Update()
{
	//�t���[���̍X�V
	this->m_Frame.Counter++;

	if (this->m_Frame.Counter > this->m_Frame.Criteria)
	{
		//�t���[���J�E���^���O�ɖ߂�
		this->m_Frame.Counter = 0;

		//�e�N�X�`���A�j���[�V��������i�߂�
		this->m_Info.CurrentTexture++;
		this->m_Info.CurrentTexture %= this->m_Info.TotalTexture;

		//UV�l���X�V����
		this->m_Info.StartUVPosition.x
			= this->m_Info.SizeUV.x * (this->m_Info.CurrentTexture % this->m_Info.CutNum.x);
		this->m_Info.StartUVPosition.y
			= this->m_Info.SizeUV.y * (this->m_Info.CurrentTexture / this->m_Info.CutNum.x);
	}
}
void Texture::Update(int index)
{
	//�t���[���̍X�V
	this->m_Frame.Counter++;

	if (this->m_Frame.Counter > this->m_Frame.Criteria)
	{
		//�t���[���J�E���^���O�ɖ߂�
		this->m_Frame.Counter = 0;

		//�e�N�X�`���A�j���[�V��������i�߂�
		this->m_Info.CurrentTexture++;
		this->m_Info.CurrentTexture %= this->m_Info.TotalTexture;

		//UV�l���X�V����
		this->m_Info.StartUVPosition.x
			= this->m_Info.SizeUV.x * (this->m_Info.CurrentTexture % this->m_Info.CutNum.x);
		this->m_Info.StartUVPosition.y
			= this->m_Info.SizeUV.y * (this->m_Info.CutNum.y * (index % this->m_Info.CutNum.y));
	}
}

/*===================================================================
	�e�N�X�`���ԍ����w��
===================================================================*/
void Texture::SetCurrentTexture(int frame)
{
	m_Info.CurrentTexture = frame - 1;
	this->m_Frame.Counter = m_Frame.Criteria + 1;
}

/*===================================================================
	�e�N�X�`����ID�ύX
===================================================================*/
void Texture::SetImageID(int num)
{
	//�f�[�^���w�肳��Ă��Ȃ���Ԃł����
	if (!this->AlreadyLoaded())
	{
		this->m_Info.TextureID = num;
	}
}

/*===================================================================
	�e�N�X�`����UV�l���W�̎w��
===================================================================*/
void Texture::SetStartUVPosition(Float2 pos)
{
	this->m_Info.StartUVPosition = pos;
}

/*===================================================================
	�e�N�X�`���̕����w��
===================================================================*/
void Texture::SetTextureDirection(DIRECTION_TEXTURE dir)
{
	this->m_Direction = dir;
}

/*===================================================================
	�f�[�^�����Z�b�g����
===================================================================*/
void Texture::Reset()
{
	*this = Texture();
}

/*===================================================================
	�e�N�X�`�����擾���Ă��邩
===================================================================*/
bool Texture::AlreadyLoaded()
{
	if (this->m_Info.TextureID == -1)
		return false;

	return true;
}
