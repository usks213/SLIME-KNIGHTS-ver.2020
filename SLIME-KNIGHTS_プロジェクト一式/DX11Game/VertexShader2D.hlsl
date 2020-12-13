// 頂点シェーダー

struct VS_IN
{
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
    float2 tex : TEXCOORD0;
    float4 col : COLOR0;
};

struct VS_OUT
{
    float4 pos  : SV_POSITION;
    float4 norw : NORMAL0;
    float2 tex  : TEXCOORD0;
    float4 col  : COLOR0;
};

// コンスタントバッファ
cbuffer ConstantBuffer
{
    float4x4 World;         // ワールド変換行列
    float4x4 View;          // ビュー変換行列
    float4x4 Projection;    // 透視投影変換行列
    float4x4 Texture;        // UV座標変換行列
}

VS_OUT main(VS_IN input)
{
    VS_OUT output;
    
    // 座標変換
    output.pos = mul(input.pos, World); // ワールド座標変換
    output.pos = mul(output.pos, View); // ビュー座標変換
    
    // テクスチャ座標
    output.tex = mul(float4(input.tex, 1, 1), Texture);
    
    // 色を渡す
    output.col = input.col;
    
	return output;
}

 // ライティング(明るさの計算)
   // col = saturate(dot(nor, (float3) LightVec));   // 法線とライトの内積を取る(飽和)
   // col = col; // 明るさの補正