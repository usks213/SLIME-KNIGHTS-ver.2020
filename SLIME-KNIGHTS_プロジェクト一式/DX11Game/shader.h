//=============================================================================
//
// DirectX11 �V�F�[�_�[�v���O���� [shader.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/05/31	�V�F�[�_�[�̍쐬
//
//=============================================================================
#pragma once


//===== �C���N���[�h�� =====
#include "main.h"

//===== �N���X��` =====
class CShader
{
private:
	ID3D11VertexShader* m_pVertexShader;	// ���_�V�F�[�_�[
	ID3D11PixelShader*	m_pPixelShader;		// �s�N�Z���V�F�[�_�[

	PBYTE m_pbVertexShaderData;				// ���_�V�F�[�_�[�f�[�^
	long  m_lVertexShaderSize;				// ���_�V�F�[�_�[�T�C�Y
public:
	CShader();								// �R���X�g���N�^
	~CShader();								// �f�X�g���N�^
	HRESULT LoadShader(ID3D11Device* pDevice, const char *pVertexFileName, const char *pPixelFileName);	// �V�F�[�_�[����
	HRESULT LoadVertexShader(ID3D11Device* pDevice, const char *pVertexFileName);						// ���_�V�F�[�_�[����
	HRESULT LoadPixelShader(ID3D11Device* pDevice, const char *pPixelFileName);							// �s�N�Z���V�F�[�_�[����
	// �Q�b�g�֐�
	ID3D11VertexShader* GetVertexShader() { return m_pVertexShader; }
	ID3D11PixelShader* GetPixelShader() { return m_pPixelShader; }

	PBYTE GetVertexShaderData() { return m_pbVertexShaderData; }
	long GetVertexShaderSize() { return m_lVertexShaderSize; }

};
