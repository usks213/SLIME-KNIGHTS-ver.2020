//=============================================================================
//
// DirectX11 �e�N�X�`���ǂݍ��� [texture.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/06/04	�e�N�X�`���ǂݍ��݂̍쐬
//
//=============================================================================

//===== �C���N���[�h�� =====
#include "texture.h"
#include "DirectX11.h"
#include <memory.h>
#include <stdlib.h>
#pragma comment(lib, "DirectXTex")


//===== �}�N����` =====
#define _CRT_SECURE_NO_WARNINGS

using namespace DirectX;




//==========================
//	�R���X�g���N�^
//==========================
CTexture::CTexture()
{
	// ������
	m_pTextureResourceView = NULL;
}


//==========================
//	�f�X�g���N�^
//==========================
CTexture::~CTexture()
{
	// �e�N�X�`�����\�[�X�r���[�̉��
	if (NULL != m_pTextureResourceView)
	{
		m_pTextureResourceView->Release();
		m_pTextureResourceView = NULL;
	}
}


//==========================
//	�e�N�X�`���̐���
//==========================
HRESULT CTexture::CreateTexture(ID3D11Device* pDevice, const wchar_t* szFileName, TexMetadata* pTexInfo)
{
	m_pTextureResourceView = nullptr;
	
	TexMetadata meta;
	ScratchImage image;
	WCHAR wszExt[_MAX_EXT];
	_wsplitpath(szFileName, nullptr, nullptr, nullptr, wszExt);
	HRESULT hr;
	if (_wcsicmp(wszExt, L".tga") == 0)
		hr = LoadFromTGAFile(szFileName, &meta, image);
	else if (_wcsicmp(wszExt, L".dds") == 0)
		hr = LoadFromDDSFile(szFileName, 0, &meta, image);
	else
		hr = LoadFromWICFile(szFileName, 0, &meta, image);
	if (FAILED(hr)) return hr;
	if (pTexInfo) *pTexInfo = meta;
	return CreateShaderResourceView(pDevice, image.GetImages(), image.GetImageCount(), meta, &m_pTextureResourceView);

	return 0;
}


//========================================
//
//	���[�h�e�N�X�`��
//
//========================================
unsigned int CTexture::LoadTexture(const char* FileName)
{
	HRESULT hr = S_OK;

	wchar_t ws[100];

	mbstowcs(ws, FileName, 100);

	hr = CreateTexture(CDirectX11::GetDevice(), ws);

	if (FAILED(hr)) return 0;

	return 1;
}

//========================================
//
//	�e�N�X�`���̉��
//
//========================================
void CTexture::UnloadTexture()
{
	// �e�N�X�`�����\�[�X�r���[�̉��
	if (NULL != m_pTextureResourceView)
	{
		m_pTextureResourceView->Release();
		m_pTextureResourceView = NULL;
	}
}

//========================================
//
//	�e�N�X�`���̉��
//
//========================================
void CTexture::UnloadTexture(unsigned int Texture)
{


}

// �t�@�C�����琶��
//HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
//	_In_z_ const wchar_t* szFileName,
//	_Out_opt_ ID3D11ShaderResourceView** textureView,
//	_Out_opt_ TexMetadata* pTexInfo)
//{
//	*textureView = nullptr;
//	TexMetadata meta;
//	ScratchImage image;
//	WCHAR wszExt[_MAX_EXT];
//	_wsplitpath(szFileName, nullptr, nullptr, nullptr, wszExt);
//	HRESULT hr;
//	if (_wcsicmp(wszExt, L".tga") == 0)
//		hr = LoadFromTGAFile(szFileName, &meta, image);
//	else if (_wcsicmp(wszExt, L".dds") == 0)
//		hr = LoadFromDDSFile(szFileName, 0, &meta, image);
//	else
//		hr = LoadFromWICFile(szFileName, 0, &meta, image);
//	if (FAILED(hr)) return hr;
//	if (pTexInfo) *pTexInfo = meta;
//	return CreateShaderResourceView(d3dDevice, image.GetImages(), image.GetImageCount(), meta, textureView);
//}