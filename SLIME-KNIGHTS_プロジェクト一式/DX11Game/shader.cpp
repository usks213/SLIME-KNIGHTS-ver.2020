//=============================================================================
//
// DirectX11 シェーダープログラム [shader.cpp]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/05/31	シェーダーの作成
//
//=============================================================================

//===== インクルード部 =====
#include "shader.h"
#include <stdio.h>


//===== プロトタイプ宣言 =====
int LoadFile(const char *pFileName, PBYTE *pbData, long *plSize);



//==========================
//	コンストラクタ
//==========================
CShader::CShader()
{
	// 初期化
	m_pVertexShader = NULL;
	m_pPixelShader  = NULL;
	m_pbVertexShaderData = NULL;
	m_lVertexShaderSize = 0;
}


//===========================
//	デストラクタ
//===========================
CShader::~CShader()
{
	// 頂点シェーダーの解放
	if (NULL != m_pVertexShader)
	{
		m_pVertexShader->Release();
		m_pVertexShader = NULL;
	}

	// ピクセルシェーダーの解放
	if (NULL != m_pPixelShader)
	{
		m_pPixelShader->Release();
		m_pPixelShader = NULL;
	}

	// シェーダーデータの解放
	if (NULL != m_pbVertexShaderData)
	{
		delete[] m_pbVertexShaderData;	// メモリ解放
		m_pbVertexShaderData = NULL;
	}

	// シェーダーサイズのリセット
	m_lVertexShaderSize = 0;
}


//=====================================
//	頂点、ピクセルシェーダーの生成
//=====================================
HRESULT CShader::LoadShader(ID3D11Device* pDevice, const char *pVertexFileName, const char *pPixelFileName)
{
	// 判定用
	HRESULT hr = S_OK;

	// 頂点シェーダーの生成
	hr = LoadVertexShader(pDevice, pVertexFileName);
	// エラー処理
	if (FAILED(hr)) return hr;

	// ピクセルシェーダー
	hr = LoadPixelShader(pDevice, pPixelFileName);
	// エラー処理
	if (FAILED(hr)) return hr;

	return hr;
}


//================================
//	頂点シェーダーの生成
//================================
HRESULT CShader::LoadVertexShader(ID3D11Device* pDevice, const char *pVertexFileName)
{
	// 判定用
	HRESULT hr = S_OK;
	// 読み込むデータの先頭ポインタ
	PBYTE pbData = NULL;
	// 読み込むデータの数
	long lSize = 0L;

	// シェーダーファイルの読み込み
	if (LoadFile(pVertexFileName, &pbData, &lSize) == 0)
	{
		return E_FAIL;
	}

	// レイアウト用にメンバに格納
	m_pbVertexShaderData = pbData;
	m_lVertexShaderSize  = lSize;
	
	// 頂点シェーダーの作成
	hr = pDevice->CreateVertexShader(m_pbVertexShaderData, m_lVertexShaderSize, NULL, &m_pVertexShader);
	// エラー処理
	if (FAILED(hr))
	{
		delete[] m_pbVertexShaderData;	// メモリ解放
		return hr;
	}

	return hr;
}


//================================
//	ピクセルシェーダーの生成
//================================
HRESULT CShader::LoadPixelShader(ID3D11Device* pDevice, const char *pPixelFileName)
{
	// 判定用
	HRESULT hr = S_OK;
	// 読み込むデータの先頭ポインタ
	PBYTE pbData = NULL;
	// 読み込むデータの数
	long lSize = 0L;

	// シェーダーファイルの読み込み
	if (LoadFile(pPixelFileName, &pbData, &lSize) == 0)
	{
		return E_FAIL;
	}

	// ピクセルシェーダーの作成
	hr = pDevice->CreatePixelShader(pbData, lSize, NULL, &m_pPixelShader);
	// エラー処理
	if (FAILED(hr))
	{
		delete[] pbData;	// メモリ解放
		return hr;
	}

	return hr;
}


//==================================
//	シェーダーファイルの読み込み
//==================================
int LoadFile(const char *pFileName, PBYTE *pbData, long *plSize)
{
	// ファイルポインタ
	FILE *fp = NULL;

	// ファイルオープン
	fopen_s(&fp, pFileName, "rb");
	if (fp == NULL) return 0;

	// ファイルサイズ
	fseek(fp, 0, SEEK_END);
	*plSize = ftell(fp);		// ファイルの文字数
	// ファイルデータ
	fseek(fp, 0, SEEK_SET);
	*pbData = new BYTE[*plSize];	// メモリ確保
	// ファイルデータの読み込み
	fread_s(*pbData, *plSize, *plSize, 1, fp);

	// ファイルクローズ
	fclose(fp);

	return *plSize;
}