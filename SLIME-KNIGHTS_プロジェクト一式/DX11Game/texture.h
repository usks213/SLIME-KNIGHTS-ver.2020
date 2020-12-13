//=============================================================================
//
// DirectX11 �e�N�X�`���ǂݍ��� [texture.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/06/04	�e�N�X�`���ǂݍ��݂̍쐬
//
//=============================================================================
#pragma once

//===== �C���N���[�h�� =====
#include "main.h"
#include "DirectXTex.h"
#include <stdint.h>


//===== �N���X��` =====
class CTexture
{
public:
	ID3D11ShaderResourceView*	m_pTextureResourceView;		// �e�N�X�`�����\�[�X�r���[

public:
	CTexture();
	~CTexture();
	HRESULT CreateTexture(ID3D11Device* pDevice, const wchar_t* szFileName, TexMetadata* pTexInfo = nullptr);
	unsigned int LoadTexture(const char* FileName);
	void UnloadTexture();
	static void UnloadTexture(unsigned int Texture);
};

