
cbuffer cbuff0 : register(b0)
{
	float4 color; // 色(RGBA)
	matrix mat; // ３Ｄ変換行列
};

//頂点シェーダーの出力構造体
//(頂点シェーダからピクセルシェーダへのやり取りに使用する)
struct VSOutput
{
	//システム用頂点座標
	float4 svpos : SV_POSITION;
	//uv値
	float2 uv : TEXCOORD;
};