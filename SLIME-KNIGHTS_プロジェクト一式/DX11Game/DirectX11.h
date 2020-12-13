//=============================================================================
//
// DirectX11������ [sample.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	�J������
//
//	2020/05/30	DirectX11�̏�����
//
//=============================================================================
#pragma once

//===== �C���N���[�h�� =====
#include "main.h"

// �萔��`
enum EBlendState
{
	BS_NONE = 0,	// �����������Ȃ�
	BS_ALPHABLEND,	// ����������
	BS_ADDITIVE,	// ���Z����
	BS_SUBTRACTION,	// ���Z����

	MAX_BLENDSTATE,
};

//===== �N���X��` =====
class CDirectX11
{
private:
	static ID3D11Device*			m_pDevice;				// �f�o�C�X
	static ID3D11DeviceContext*	m_pDeviceContext;		// �f�o�C�X�R���e�L�X�g
	static IDXGISwapChain*			m_pSwapChain;			// �X���b�v�`�F�[��
	static ID3D11RenderTargetView*	m_pRenderTargetView;	// �����_�[�^�[�Q�b�g�r���[(�����_�����O�p�C�v���C������A�E�g�v�b�g�����s�N�Z�����)
	static ID3D11Texture2D*		m_pDepthStencilTexture;	// �[�x/�X�e���V���o�b�t�@
	static ID3D11DepthStencilView*	m_pDepthStencilView;	// �[�x/�X�e���V���r���[
	static D3D11_VIEWPORT			m_Viewport;				// �r���[�|�[�g
	static ID3D11BlendState*		m_pBlendState[MAX_BLENDSTATE];			// �u�����h �X�e�[�g
public:
			CDirectX11();
			~CDirectX11();
	static HRESULT Create(HWND hwnd);	// Init
	static void	Release();			// Uninit
	static void	StartRender();			// Draw
	static void	EndRender();			// Draw
	static void SetBlendState(int nBlendState);

	// �Q�b�g�֐�
	static ID3D11Device*		GetDevice() { return m_pDevice; }
	static ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; }

};
