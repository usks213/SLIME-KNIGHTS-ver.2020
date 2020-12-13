//=============================================================================
//
// DirectX11初期化 [sample.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/05/30	DirectX11の初期化
//
//=============================================================================
#pragma once

//===== インクルード部 =====
#include "main.h"

// 定数定義
enum EBlendState
{
	BS_NONE = 0,	// 半透明合成なし
	BS_ALPHABLEND,	// 半透明合成
	BS_ADDITIVE,	// 加算合成
	BS_SUBTRACTION,	// 減算合成

	MAX_BLENDSTATE,
};

//===== クラス定義 =====
class CDirectX11
{
private:
	static ID3D11Device*			m_pDevice;				// デバイス
	static ID3D11DeviceContext*	m_pDeviceContext;		// デバイスコンテキスト
	static IDXGISwapChain*			m_pSwapChain;			// スワップチェーン
	static ID3D11RenderTargetView*	m_pRenderTargetView;	// レンダーターゲットビュー(レンダリングパイプラインからアウトプットされるピクセル情報)
	static ID3D11Texture2D*		m_pDepthStencilTexture;	// 深度/ステンシルバッファ
	static ID3D11DepthStencilView*	m_pDepthStencilView;	// 深度/ステンシルビュー
	static D3D11_VIEWPORT			m_Viewport;				// ビューポート
	static ID3D11BlendState*		m_pBlendState[MAX_BLENDSTATE];			// ブレンド ステート
public:
			CDirectX11();
			~CDirectX11();
	static HRESULT Create(HWND hwnd);	// Init
	static void	Release();			// Uninit
	static void	StartRender();			// Draw
	static void	EndRender();			// Draw
	static void SetBlendState(int nBlendState);

	// ゲット関数
	static ID3D11Device*		GetDevice() { return m_pDevice; }
	static ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; }

};
