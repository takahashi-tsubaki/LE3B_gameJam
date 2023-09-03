#include "Sprite.hlsli"

VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD)
{
	VSOutput output;//ピクセルシェーダに渡す値
	output.svpos = mul(mat, pos);//座標に行輝を計算
	output.uv = uv;
	return output;
}