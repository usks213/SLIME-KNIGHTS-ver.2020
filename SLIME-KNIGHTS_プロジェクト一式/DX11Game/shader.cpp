//=============================================================================
//
// DirectX11 �V�F�[�_�[�v���O���� [shader.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/05/31	�V�F�[�_�[�̍쐬
//
//=============================================================================

//===== �C���N���[�h�� =====
#include "shader.h"
#include <stdio.h>


//===== �v���g�^�C�v�錾 =====
int LoadFile(const char *pFileName, PBYTE *pbData, long *plSize);



//==========================
//	�R���X�g���N�^
//==========================
CShader::CShader()
{
	// ������
	m_pVertexShader = NULL;
	m_pPixelShader  = NULL;
	m_pbVertexShaderData = NULL;
	m_lVertexShaderSize = 0;
}


//===========================
//	�f�X�g���N�^
//===========================
CShader::~CShader()
{
	// ���_�V�F�[�_�[�̉��
	if (NULL != m_pVertexShader)
	{
		m_pVertexShader->Release();
		m_pVertexShader = NULL;
	}

	// �s�N�Z���V�F�[�_�[�̉��
	if (NULL != m_pPixelShader)
	{
		m_pPixelShader->Release();
		m_pPixelShader = NULL;
	}

	// �V�F�[�_�[�f�[�^�̉��
	if (NULL != m_pbVertexShaderData)
	{
		delete[] m_pbVertexShaderData;	// ���������
		m_pbVertexShaderData = NULL;
	}

	// �V�F�[�_�[�T�C�Y�̃��Z�b�g
	m_lVertexShaderSize = 0;
}


//=====================================
//	���_�A�s�N�Z���V�F�[�_�[�̐���
//=====================================
HRESULT CShader::LoadShader(ID3D11Device* pDevice, const char *pVertexFileName, const char *pPixelFileName)
{
	// ����p
	HRESULT hr = S_OK;

	// ���_�V�F�[�_�[�̐���
	hr = LoadVertexShader(pDevice, pVertexFileName);
	// �G���[����
	if (FAILED(hr)) return hr;

	// �s�N�Z���V�F�[�_�[
	hr = LoadPixelShader(pDevice, pPixelFileName);
	// �G���[����
	if (FAILED(hr)) return hr;

	return hr;
}


//================================
//	���_�V�F�[�_�[�̐���
//================================
HRESULT CShader::LoadVertexShader(ID3D11Device* pDevice, const char *pVertexFileName)
{
	// ����p
	HRESULT hr = S_OK;
	// �ǂݍ��ރf�[�^�̐擪�|�C���^
	PBYTE pbData = NULL;
	// �ǂݍ��ރf�[�^�̐�
	long lSize = 0L;

	// �V�F�[�_�[�t�@�C���̓ǂݍ���
	if (LoadFile(pVertexFileName, &pbData, &lSize) == 0)
	{
		return E_FAIL;
	}

	// ���C�A�E�g�p�Ƀ����o�Ɋi�[
	m_pbVertexShaderData = pbData;
	m_lVertexShaderSize  = lSize;
	
	// ���_�V�F�[�_�[�̍쐬
	hr = pDevice->CreateVertexShader(m_pbVertexShaderData, m_lVertexShaderSize, NULL, &m_pVertexShader);
	// �G���[����
	if (FAILED(hr))
	{
		delete[] m_pbVertexShaderData;	// ���������
		return hr;
	}

	return hr;
}


//================================
//	�s�N�Z���V�F�[�_�[�̐���
//================================
HRESULT CShader::LoadPixelShader(ID3D11Device* pDevice, const char *pPixelFileName)
{
	// ����p
	HRESULT hr = S_OK;
	// �ǂݍ��ރf�[�^�̐擪�|�C���^
	PBYTE pbData = NULL;
	// �ǂݍ��ރf�[�^�̐�
	long lSize = 0L;

	// �V�F�[�_�[�t�@�C���̓ǂݍ���
	if (LoadFile(pPixelFileName, &pbData, &lSize) == 0)
	{
		return E_FAIL;
	}

	// �s�N�Z���V�F�[�_�[�̍쐬
	hr = pDevice->CreatePixelShader(pbData, lSize, NULL, &m_pPixelShader);
	// �G���[����
	if (FAILED(hr))
	{
		delete[] pbData;	// ���������
		return hr;
	}

	return hr;
}


//==================================
//	�V�F�[�_�[�t�@�C���̓ǂݍ���
//==================================
int LoadFile(const char *pFileName, PBYTE *pbData, long *plSize)
{
	// �t�@�C���|�C���^
	FILE *fp = NULL;

	// �t�@�C���I�[�v��
	fopen_s(&fp, pFileName, "rb");
	if (fp == NULL) return 0;

	// �t�@�C���T�C�Y
	fseek(fp, 0, SEEK_END);
	*plSize = ftell(fp);		// �t�@�C���̕�����
	// �t�@�C���f�[�^
	fseek(fp, 0, SEEK_SET);
	*pbData = new BYTE[*plSize];	// �������m��
	// �t�@�C���f�[�^�̓ǂݍ���
	fread_s(*pbData, *plSize, *plSize, 1, fp);

	// �t�@�C���N���[�Y
	fclose(fp);

	return *plSize;
}