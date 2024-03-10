/*=========================================================================
	Date : 2021/12/26(土)	Texture.h
		Author : がむしるぉ
		Update :
=========================================================================*/
#include "main.h"


#define NOT_FOUND_PARTS 999

class Sprite;

//テクスチャの向き
enum class DIRECTION_TEXTURE
{
	RIGHT,	//右向き
	LEFT,	//左向き
};

//アニメーションに必要なフレームデータ
struct TextureFrame
{
	UINT Criteria	= 0;		//切り替え基準値
	UINT Counter	= 0;		//フレームのカウンタ
};

//アニメーションに必要な画像情報
struct TextureInfo
{
	int				TextureID		= -1;	//テクスチャID
	int				TotalTexture	= 0;	//テクスチャの総枚数(num.x * num.y)
	int				CurrentTexture	= 0;	//現在のテクスチャ枚数
	math::Int2		CutNum;					//縦と横のカット枚数
	math::Float2	StartUVPosition;		//UV値の開始座標
	math::Float2	SizeUV;					//1枚のサイズ
};

class Texture
{
public:
	Texture();
	~Texture();

public:
	/****************************************************************************
		@ brief テクスチャデータの生成処理
		@ param 
			fileName	: ファイルの名前
			column		: テクスチャのカット数(横)
			row			: テクスチャのカット数(縦)
			frame		: 更新フレーム基準
	****************************************************************************/
	void Create(const char* fileName, int column, int row, int frame = 1);
	
	/****************************************************************************
		@ brief テクスチャデータの生成処理
		@ comment
			アニメーションの更新処理
	****************************************************************************/
	void Update();
	void Update(int index);

public:
	void SetCurrentTexture(int frame);					//開始フレームを設定する
	void SetImageID(int num);							//テクスチャのIDを指定する
	void SetStartUVPosition(math::Float2 UVpos);		//UV座標を直接指定する
	void SetTextureDirection(DIRECTION_TEXTURE dir);	//テクスチャの向きを決める

public:
	void Reset();

public:
	int				GetCurrentTexture() { return m_Info.CurrentTexture; }	//現在のテクスチャ番号を取得
	int				GetFrameCounter()	{ return m_Frame.Counter; }			//現在のフレームカウンタを取得
	int				GetTextureID()		{ return m_Info.TextureID; }		//テクスチャデータを取得する
	int				GetTotalTexture()	{ return m_Info.TotalTexture; }		//テクスチャアニメーションの合計枚数を取得
	math::Float2	GetTextureUVSize()	{ return m_Info.SizeUV; }			//テクスチャサイズを取得する

public:
	bool AlreadyLoaded();						//テクスチャが既に読み込まれているか true 読み込まれている 

private:
	TextureFrame		m_Frame;		//フレームデータ
	TextureInfo			m_Info;			//画像情報	
	DIRECTION_TEXTURE	m_Direction;	//テクスチャの方向

private:
	friend class Sprite;
};



