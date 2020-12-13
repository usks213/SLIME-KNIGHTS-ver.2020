// ピクセルシェーダー

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 posw : POSITION0;
    float4 norw : NORMAL0;
    float2 tex : TEXCOORD0;
    float4 col : COLOR0;
};

// 点光源
struct ConstantPointLight
{
    float4 pos;         // 座標(x,y,z)
    float4 diffuse;     // 拡散(r,g,b)
    float4 specular;    // 反射(r,g,b)
    float4 attenuate;   // 減衰(a,b,c)
};
// マテリアル
struct ConstantMaterial
{
    float4 ambient;     // 環境(r,g,b)
    float4 diffuse;     // 拡散(r,g,b)
    float4 specular;    // 反射(r,g,b,光沢度係数)
};
// 定数バッファ(ライティング)
cbuffer ConstantLightBuffer
{
    float4 eyePos;                  // 視点座標
    float4 ambient;                 // 環境光(r,g,b)
    ConstantPointLight pointLight;  // 点光源
    ConstantMaterial material;      // 物体の質感
};

// テクスチャ
Texture2D    myTexture : register(t0);  // テクスチャ
SamplerState mySampler : register(s0);  // サンプラー


float4 ps_main(PS_IN input) : SV_TARGET
{
    // 変数
    float3 nor;         // 法線
    float3 viewDir;     // 視点へのベクトル
    float3 lightDir;    // ライトへのベクトル
    float3 reflection;  // 反射ベクトル
    float lightLen;     // ライトまでの距離
    float attenuate;    // 光の減衰
    float3 ambientColor;    // 環境
    float3 deffuseColor;    // 拡散
    float3 specularColor;   // 反射光ベクトル
    float4 textureColor;    // テクスチャ
    
    // 初期化
    nor = normalize(input.norw.xyz);
    viewDir = normalize(eyePos.xyz - input.posw.xyz);
    lightDir = pointLight.pos.xyz - input.posw.xyz;
    lightLen = length(lightDir);
    lightDir = normalize(lightDir);
    reflection = 2.0f * nor * dot(nor, lightDir) - lightDir;
    attenuate = saturate(1.0f / (pointLight.attenuate.x + pointLight.attenuate.y * lightLen + pointLight.attenuate.z * lightLen * lightLen));
    
    // テクスチャ
    textureColor = myTexture.Sample(mySampler, input.tex);
    
    // 色決め
    ambientColor =                                  textureColor.rgb *  material.ambient.xyz * ambient.xyz;
    deffuseColor = saturate(dot(lightDir, nor)) *   textureColor.rgb *  material.diffuse.xyz * pointLight.diffuse.xyz * attenuate;
    specularColor = pow(saturate(dot(reflection, viewDir)),         material.specular.w) * material.specular.xyz * pointLight.specular.xyz;
    
    return float4(saturate(ambientColor + deffuseColor + specularColor), textureColor.a);

}