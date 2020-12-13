// ピクセルシェーダー

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 norw : NORMAL0;
    float2 tex : TEXCOORD0;
    float4 col : COLOR0;
};

// コンスタントバッファ
cbuffer ConstantColorBuffer
{
    float4 color;
}

// テクスチャ
Texture2D    myTexture : register(t0);  // テクスチャ
SamplerState mySampler : register(s0);  // サンプラー


float4 main(PS_IN input) : SV_TARGET
{
    // 変数
    float4 textureColor;    // テクスチャ

    // テクスチャ
    textureColor = myTexture.Sample(mySampler, input.tex);
    
    
    return textureColor.rgba * input.col * color;

}