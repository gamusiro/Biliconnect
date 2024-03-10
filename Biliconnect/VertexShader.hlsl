/*===========================================================================
	Date : 2022/02/08(��)	VertexShader.hlsl
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "ShaderStructure.hlsli"

//2D�ϊ��s��f�[�^
cbuffer ConstantBuffer : register(b0)
{
    matrix Translate2D;
}

//���_�V�F�[�_
OUTPUT vsmain( INPUT input )
{
    OUTPUT output = (OUTPUT) 0;
	
    output.Position = mul(input.Position, Translate2D);
    output.Normal   = input.Normal;
    output.Color    = input.Color;
    output.TexCoord = input.TexCoord;
    
    return output;
}