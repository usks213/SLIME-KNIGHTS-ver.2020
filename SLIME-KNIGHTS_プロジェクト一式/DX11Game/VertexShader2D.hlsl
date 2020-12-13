// ���_�V�F�[�_�[

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

// �R���X�^���g�o�b�t�@
cbuffer ConstantBuffer
{
    float4x4 World;         // ���[���h�ϊ��s��
    float4x4 View;          // �r���[�ϊ��s��
    float4x4 Projection;    // �������e�ϊ��s��
    float4x4 Texture;        // UV���W�ϊ��s��
}

VS_OUT main(VS_IN input)
{
    VS_OUT output;
    
    // ���W�ϊ�
    output.pos = mul(input.pos, World); // ���[���h���W�ϊ�
    output.pos = mul(output.pos, View); // �r���[���W�ϊ�
    
    // �e�N�X�`�����W
    output.tex = mul(float4(input.tex, 1, 1), Texture);
    
    // �F��n��
    output.col = input.col;
    
	return output;
}

 // ���C�e�B���O(���邳�̌v�Z)
   // col = saturate(dot(nor, (float3) LightVec));   // �@���ƃ��C�g�̓��ς����(�O�a)
   // col = col; // ���邳�̕␳