/*===========================================================================
	Date : 2022/02/08(��)	PixelShader.hlsl
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "ShaderStructure.hlsli"

Texture2D       g_Texture       : register(t0);
SamplerState    g_SamplerState  : register(s0);

//�}�e���A���o�b�t�@
cbuffer MaterialBuffer : register(b1)
{
    Material material;
}

//�s�N�Z���V�F�[�_
float4 psmain(OUTPUT input) : SV_TARGET
{
    float4 outColor = float4(0, 0, 0, 0);
    
    if (material.noTexSampling == 1)
    {//�e�N�X�`���𗘗p����
        outColor  = g_Texture.Sample(g_SamplerState, input.TexCoord);
        outColor *= input.Color;
    }
    else
    {//�e�N�X�`���𗘗p���Ȃ�
        outColor = input.Color;
    }
    return outColor;
}