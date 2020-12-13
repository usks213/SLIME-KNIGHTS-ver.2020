//=============================================================================
//
// DirectX11 テクスチャ読み込み [texture.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/06/04	テクスチャ読み込みの作成
//
//=============================================================================

//===== インクルード部 =====
#include "texture.h"
#include "DirectX11.h"
#include <memory.h>
#include <stdlib.h>
#pragma comment(lib, "DirectXTex")


//===== マクロ定義 =====
#define _CRT_SECURE_NO_WARNINGS

using namespace DirectX;




//==========================
//	コンストラクタ
//==========================
CTexture::CTexture()
{
	// 初期化
	m_pTextureResourceView = NULL;
}


//==========================
//	デストラクタ
//==========================
CTexture::~CTexture()
{
	// テクスチャリソースビューの解放
	if (NULL != m_pTextureResourceView)
	{
		m_pTextureResourceView->Release();
		m_pTextureResourceView = NULL;
	}
}


//==========================
//	テクスチャの生成
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
//	ロードテクスチャ
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
//	テクスチャの解放
//
//========================================
void CTexture::UnloadTexture()
{
	// テクスチャリソースビューの解放
	if (NULL != m_pTextureResourceView)
	{
		m_pTextureResourceView->Release();
		m_pTextureResourceView = NULL;
	}
}

//========================================
//
//	テクスチャの解放
//
//========================================
void CTexture::UnloadTexture(unsigned int Texture)
{


}

// ファイルから生成
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