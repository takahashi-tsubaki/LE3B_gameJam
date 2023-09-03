#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);	//0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);	//1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);		//0番スロットに設定されたサンプラー


float4 main(VSOutput input) : SV_TARGET
{
    float2 add = { 0.5f, 0.0f };
    float4 texcolor0 = tex0.Sample(smp, input.uv);
    
    float offSetU = 1 / 1280.0f;
    float offSetV = 1 / 720.0f;
    
    int size = 2;
	
    float4 sum = float4(0, 0, 0, 0);
   
	
    for (int x = -size; x <= size; ++x)
    {
        for (int y = -size; y <= size; ++y)
        {
            float2 offSet = float2(x, y) * float2(offSetU, offSetV);
            float4 texcolor0 = tex0.Sample(smp, input.uv + offSet);
            sum += texcolor0;

        }

    }

    float kernelArea = (2 * size + 1) * (2 * size + 1);
    float4 averageColor = sum / kernelArea;
    float4 texcolor1 = tex1.Sample(smp, input.uv);

    float4 color = averageColor;
    if (fmod(input.uv.y, 0.1f) < 0.05f)
    {
        color = 1 - texcolor0;
    }

    return float4(color.rgb, 1);
}