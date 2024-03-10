/*===========================================================================
	Date : 2022/02/08(火)	VertexShader.hlsl
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
//入力データの構造体
struct INPUT
{
    float4 Position : POSITION0;
    float4 Normal	: NORMAL0;
	float4 Color	: COLOR0;
    float2 TexCoord : TEXCOORD0;
};

//出力データの構造体
struct OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Normal	: NORMAL0;
	float4 Color	: COLOR0;
    float2 TexCoord : TEXCOORD0;
};

//マテリアル構造体
struct Material
{
    int     noTexSampling;
    float   Dummy[3];
};