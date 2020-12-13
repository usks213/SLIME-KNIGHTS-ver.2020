//=============================================================================
//
// DirectX11初期化 [polygon.h]
// Author : KOSHI USAMI
//
//=============================================================================
//
//	開発履歴
//
//	2020/05/31	ポリゴン描画の作成
//
//=============================================================================
#pragma once

//===== インクルード部 =====
#include "main.h"
#include "shader.h"
#include "model.h"
#include "texture.h"
#include "source/transform.h"


//===== 構造体定義 =====
//struct Transform
//{
//	XMFLOAT3 pos = {0.0f, 0.0f, 0.0f};	// 移動量
//	XMFLOAT3 rot = {0.0f, 0.0f, 0.0f};	// 回転量
//	XMFLOAT3 size = {1.0f, 1.0f, 1.0f};	// サイズ
//	XMFLOAT2 texPos = {0.0f, 0.0f};		// UV座標
//	XMFLOAT2 texSize = {1.0f, 1.0f};	// UVサイズ
//};
#define AngleToRadian(a) (a / 180.0f * 3.1415f)


//===== クラス定義 =====

// 前定義
class CSprite;

class CPolygon
{
public:
	ID3D11Buffer* m_pVertexBuffer;			// 頂点バッファ
	ID3D11Buffer* m_pIndexBuffer;			// インデックスバッファ
	ID3D11InputLayout*	m_pInputLayout;		// 入力レイアウト

	ID3D11SamplerState*	m_pSampler;			// サンプラー

	ID3D11Buffer* m_pConstantMatrixBuffer;	// コンスタントバッファ(行列座標変換)
	ID3D11Buffer* m_pConstantColorBuffer;	// コンスタントバッファ(カラー)

	// 外部データ
	CModel *m_pModel;
	CShader *m_pShader;

public:
	CPolygon();
	~CPolygon();
	HRESULT Create(ID3D11Device *pDevice, CModel *pModel, CShader *pShader);
	void Draw(ID3D11DeviceContext *pDeviceContext, CTransform *pTrans, CTexture *pTexture, CSprite *pStr, bool bCamera = true);
	// ゲット関数

	// セット関数

};
