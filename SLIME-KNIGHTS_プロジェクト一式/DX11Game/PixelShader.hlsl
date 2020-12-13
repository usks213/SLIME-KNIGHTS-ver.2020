// �s�N�Z���V�F�[�_�[

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 posw : POSITION0;
    float4 norw : NORMAL0;
    float2 tex : TEXCOORD0;
    float4 col : COLOR0;
};

// �_����
struct ConstantPointLight
{
    float4 pos;         // ���W(x,y,z)
    float4 diffuse;     // �g�U(r,g,b)
    float4 specular;    // ����(r,g,b)
    float4 attenuate;   // ����(a,b,c)
};
// �}�e���A��
struct ConstantMaterial
{
    float4 ambient;     // ��(r,g,b)
    float4 diffuse;     // �g�U(r,g,b)
    float4 specular;    // ����(r,g,b,����x�W��)
};
// �萔�o�b�t�@(���C�e�B���O)
cbuffer ConstantLightBuffer
{
    float4 eyePos;                  // ���_���W
    float4 ambient;                 // ����(r,g,b)
    ConstantPointLight pointLight;  // �_����
    ConstantMaterial material;      // ���̂̎���
};

// �e�N�X�`��
Texture2D    myTexture : register(t0);  // �e�N�X�`��
SamplerState mySampler : register(s0);  // �T���v���[


float4 ps_main(PS_IN input) : SV_TARGET
{
    // �ϐ�
    float3 nor;         // �@��
    float3 viewDir;     // ���_�ւ̃x�N�g��
    float3 lightDir;    // ���C�g�ւ̃x�N�g��
    float3 reflection;  // ���˃x�N�g��
    float lightLen;     // ���C�g�܂ł̋���
    float attenuate;    // ���̌���
    float3 ambientColor;    // ��
    float3 deffuseColor;    // �g�U
    float3 specularColor;   // ���ˌ��x�N�g��
    float4 textureColor;    // �e�N�X�`��
    
    // ������
    nor = normalize(input.norw.xyz);
    viewDir = normalize(eyePos.xyz - input.posw.xyz);
    lightDir = pointLight.pos.xyz - input.posw.xyz;
    lightLen = length(lightDir);
    lightDir = normalize(lightDir);
    reflection = 2.0f * nor * dot(nor, lightDir) - lightDir;
    attenuate = saturate(1.0f / (pointLight.attenuate.x + pointLight.attenuate.y * lightLen + pointLight.attenuate.z * lightLen * lightLen));
    
    // �e�N�X�`��
    textureColor = myTexture.Sample(mySampler, input.tex);
    
    // �F����
    ambientColor =                                  textureColor.rgb *  material.ambient.xyz * ambient.xyz;
    deffuseColor = saturate(dot(lightDir, nor)) *   textureColor.rgb *  material.diffuse.xyz * pointLight.diffuse.xyz * attenuate;
    specularColor = pow(saturate(dot(reflection, viewDir)),         material.specular.w) * material.specular.xyz * pointLight.specular.xyz;
    
    return float4(saturate(ambientColor + deffuseColor + specularColor), textureColor.a);

}