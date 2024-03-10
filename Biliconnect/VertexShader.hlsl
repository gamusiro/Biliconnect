/*===========================================================================
	Date : 2022/02/08(火)	VertexShader.hlsl
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "ShaderStructure.hlsli"

//2D変換行列データ
cbuffer ConstantBuffer : register(b0)
{
    matrix Translate2D;
}

//頂点シェーダ
OUTPUT vsmain( INPUT input )
{
    OUTPUT output = (OUTPUT) 0;
	
    output.Position = mul(input.Position, Translate2D);
    output.Normal   = input.Normal;
    output.Color    = input.Color;
    output.TexCoord = input.TexCoord;
    
    return output;
}