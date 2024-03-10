/*===========================================================================
	Date : 2022/02/08(火)	PixelShader.hlsl
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "ShaderStructure.hlsli"

Texture2D       g_Texture       : register(t0);
SamplerState    g_SamplerState  : register(s0);

//マテリアルバッファ
cbuffer MaterialBuffer : register(b1)
{
    Material material;
}

//ピクセルシェーダ
float4 psmain(OUTPUT input) : SV_TARGET
{
    float4 outColor = float4(0, 0, 0, 0);
    
    if (material.noTexSampling == 1)
    {//テクスチャを利用する
        outColor  = g_Texture.Sample(g_SamplerState, input.TexCoord);
        outColor *= input.Color;
    }
    else
    {//テクスチャを利用しない
        outColor = input.Color;
    }
    return outColor;
}