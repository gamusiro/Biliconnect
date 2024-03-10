/*===========================================================================
	Date : 2022/02/08(��)	VertexShader.hlsl
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
//���̓f�[�^�̍\����
struct INPUT
{
    float4 Position : POSITION0;
    float4 Normal	: NORMAL0;
	float4 Color	: COLOR0;
    float2 TexCoord : TEXCOORD0;
};

//�o�̓f�[�^�̍\����
struct OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Normal	: NORMAL0;
	float4 Color	: COLOR0;
    float2 TexCoord : TEXCOORD0;
};

//�}�e���A���\����
struct Material
{
    int     noTexSampling;
    float   Dummy[3];
};