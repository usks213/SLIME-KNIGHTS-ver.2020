//=============================================================================
//
// DirectX11 シェーダープログラム [shader.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/05/31	シェーダーの作成
//
//=============================================================================
#pragma once


//===== インクルード部 =====
#include "main.h"

//===== クラス定義 =====
class CShader
{
private:
	ID3D11VertexShader* m_pVertexShader;	// 頂点シェーダー
	ID3D11PixelShader*	m_pPixelShader;		// ピクセルシェーダー

	PBYTE m_pbVertexShaderData;				// 頂点シェーダーデータ
	long  m_lVertexShaderSize;				// 頂点シェーダーサイズ
public:
	CShader();								// コンストラクタ
	~CShader();								// デストラクタ
	HRESULT LoadShader(ID3D11Device* pDevice, const char *pVertexFileName, const char *pPixelFileName);	// シェーダー生成
	HRESULT LoadVertexShader(ID3D11Device* pDevice, const char *pVertexFileName);						// 頂点シェーダー生成
	HRESULT LoadPixelShader(ID3D11Device* pDevice, const char *pPixelFileName);							// ピクセルシェーダー生成
	// ゲット関数
	ID3D11VertexShader* GetVertexShader() { return m_pVertexShader; }
	ID3D11PixelShader* GetPixelShader() { return m_pPixelShader; }

	PBYTE GetVertexShaderData() { return m_pbVertexShaderData; }
	long GetVertexShaderSize() { return m_lVertexShaderSize; }

};
