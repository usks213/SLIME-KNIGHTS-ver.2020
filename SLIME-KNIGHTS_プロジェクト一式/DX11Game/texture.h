//=============================================================================
//
// DirectX11 テクスチャ読み込み [texture.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/06/04	テクスチャ読み込みの作成
//
//=============================================================================
#pragma once

//===== インクルード部 =====
#include "main.h"
#include "DirectXTex.h"
#include <stdint.h>


//===== クラス定義 =====
class CTexture
{
public:
	ID3D11ShaderResourceView*	m_pTextureResourceView;		// テクスチャリソースビュー

public:
	CTexture();
	~CTexture();
	HRESULT CreateTexture(ID3D11Device* pDevice, const wchar_t* szFileName, TexMetadata* pTexInfo = nullptr);
	unsigned int LoadTexture(const char* FileName);
	void UnloadTexture();
	static void UnloadTexture(unsigned int Texture);
};

