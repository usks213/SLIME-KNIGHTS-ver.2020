// �s�N�Z���V�F�[�_�[

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 norw : NORMAL0;
    float2 tex : TEXCOORD0;
    float4 col : COLOR0;
};

// �R���X�^���g�o�b�t�@
cbuffer ConstantColorBuffer
{
    float4 color;
}

// �e�N�X�`��
Texture2D    myTexture : register(t0);  // �e�N�X�`��
SamplerState mySampler : register(s0);  // �T���v���[


float4 main(PS_IN input) : SV_TARGET
{
    // �ϐ�
    float4 textureColor;    // �e�N�X�`��

    // �e�N�X�`��
    textureColor = myTexture.Sample(mySampler, input.tex);
    
    
    return textureColor.rgba * input.col * color;

}