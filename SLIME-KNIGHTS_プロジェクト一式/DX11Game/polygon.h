//=============================================================================
//
// DirectX11������ [polygon.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/05/31	�|���S���`��̍쐬
//
//=============================================================================
#pragma once

//===== �C���N���[�h�� =====
#include "main.h"
#include "shader.h"
#include "model.h"
#include "texture.h"
#include "source/transform.h"


//===== �\���̒�` =====
//struct Transform
//{
//	XMFLOAT3 pos = {0.0f, 0.0f, 0.0f};	// �ړ���
//	XMFLOAT3 rot = {0.0f, 0.0f, 0.0f};	// ��]��
//	XMFLOAT3 size = {1.0f, 1.0f, 1.0f};	// �T�C�Y
//	XMFLOAT2 texPos = {0.0f, 0.0f};		// UV���W
//	XMFLOAT2 texSize = {1.0f, 1.0f};	// UV�T�C�Y
//};
#define AngleToRadian(a) (a / 180.0f * 3.1415f)


//===== �N���X��` =====

// �O��`
class CSprite;

class CPolygon
{
public:
	ID3D11Buffer* m_pVertexBuffer;			// ���_�o�b�t�@
	ID3D11Buffer* m_pIndexBuffer;			// �C���f�b�N�X�o�b�t�@
	ID3D11InputLayout*	m_pInputLayout;		// ���̓��C�A�E�g

	ID3D11SamplerState*	m_pSampler;			// �T���v���[

	ID3D11Buffer* m_pConstantMatrixBuffer;	// �R���X�^���g�o�b�t�@(�s����W�ϊ�)
	ID3D11Buffer* m_pConstantColorBuffer;	// �R���X�^���g�o�b�t�@(�J���[)

	// �O���f�[�^
	CModel *m_pModel;
	CShader *m_pShader;

public:
	CPolygon();
	~CPolygon();
	HRESULT Create(ID3D11Device *pDevice, CModel *pModel, CShader *pShader);
	void Draw(ID3D11DeviceContext *pDeviceContext, CTransform *pTrans, CTexture *pTexture, CSprite *pStr, bool bCamera = true);
	// �Q�b�g�֐�

	// �Z�b�g�֐�

};
