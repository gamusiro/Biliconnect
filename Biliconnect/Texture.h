/*=========================================================================
	Date : 2021/12/26(�y)	Texture.h
		Author : ���ނ��邧
		Update :
=========================================================================*/
#include "main.h"


#define NOT_FOUND_PARTS 999

class Sprite;

//�e�N�X�`���̌���
enum class DIRECTION_TEXTURE
{
	RIGHT,	//�E����
	LEFT,	//������
};

//�A�j���[�V�����ɕK�v�ȃt���[���f�[�^
struct TextureFrame
{
	UINT Criteria	= 0;		//�؂�ւ���l
	UINT Counter	= 0;		//�t���[���̃J�E���^
};

//�A�j���[�V�����ɕK�v�ȉ摜���
struct TextureInfo
{
	int				TextureID		= -1;	//�e�N�X�`��ID
	int				TotalTexture	= 0;	//�e�N�X�`���̑�����(num.x * num.y)
	int				CurrentTexture	= 0;	//���݂̃e�N�X�`������
	math::Int2		CutNum;					//�c�Ɖ��̃J�b�g����
	math::Float2	StartUVPosition;		//UV�l�̊J�n���W
	math::Float2	SizeUV;					//1���̃T�C�Y
};

class Texture
{
public:
	Texture();
	~Texture();

public:
	/****************************************************************************
		@ brief �e�N�X�`���f�[�^�̐�������
		@ param 
			fileName	: �t�@�C���̖��O
			column		: �e�N�X�`���̃J�b�g��(��)
			row			: �e�N�X�`���̃J�b�g��(�c)
			frame		: �X�V�t���[���
	****************************************************************************/
	void Create(const char* fileName, int column, int row, int frame = 1);
	
	/****************************************************************************
		@ brief �e�N�X�`���f�[�^�̐�������
		@ comment
			�A�j���[�V�����̍X�V����
	****************************************************************************/
	void Update();
	void Update(int index);

public:
	void SetCurrentTexture(int frame);					//�J�n�t���[����ݒ肷��
	void SetImageID(int num);							//�e�N�X�`����ID���w�肷��
	void SetStartUVPosition(math::Float2 UVpos);		//UV���W�𒼐ڎw�肷��
	void SetTextureDirection(DIRECTION_TEXTURE dir);	//�e�N�X�`���̌��������߂�

public:
	void Reset();

public:
	int				GetCurrentTexture() { return m_Info.CurrentTexture; }	//���݂̃e�N�X�`���ԍ����擾
	int				GetFrameCounter()	{ return m_Frame.Counter; }			//���݂̃t���[���J�E���^���擾
	int				GetTextureID()		{ return m_Info.TextureID; }		//�e�N�X�`���f�[�^���擾����
	int				GetTotalTexture()	{ return m_Info.TotalTexture; }		//�e�N�X�`���A�j���[�V�����̍��v�������擾
	math::Float2	GetTextureUVSize()	{ return m_Info.SizeUV; }			//�e�N�X�`���T�C�Y���擾����

public:
	bool AlreadyLoaded();						//�e�N�X�`�������ɓǂݍ��܂�Ă��邩 true �ǂݍ��܂�Ă��� 

private:
	TextureFrame		m_Frame;		//�t���[���f�[�^
	TextureInfo			m_Info;			//�摜���	
	DIRECTION_TEXTURE	m_Direction;	//�e�N�X�`���̕���

private:
	friend class Sprite;
};



