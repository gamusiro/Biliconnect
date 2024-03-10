/*===========================================================================
	Date : 2022/02/08(月)	RasterizerState.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef RASTERIZERSTATE_H_
#define RASTERIZERSTATE_H_

#include "main.h"

class GraphicsManager;

/**********************************************************
	@brief カリングモードの指定
	None : カリングモード無し		
	FRONT: カリングモードフロント	(時計回り)
	BACK : カリングモードバック	(反時計回り)
**********************************************************/
enum class CULL_MODE
{
	NONE, FRONT, BACK
};

class RasterizerState
{
public:
	RasterizerState(GraphicsManager* gm);
	~RasterizerState();

public:
	bool Create();					//生成処理
	void SetMode(CULL_MODE mode);	//モードの指定
	void Release();					//終了処理

private:
	GraphicsManager*		m_GraphicsManager;
	ID3D11RasterizerState*	m_RS_Cull_Off;
	ID3D11RasterizerState*	m_RS_Cull_CW;
	ID3D11RasterizerState*	m_RS_Cull_CCW;
};

#endif // !RASTERIZERSTATE_H_
