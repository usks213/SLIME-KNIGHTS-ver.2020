//==============================================
//								sprite.h
//	GM21 図形描画関連
//
//==============================================
//	author :	AT12A 05 宇佐美晃之
//==============================================
//	開発履歴
//
//	2020/05/22	図形描画関数の実装
//
//	2020/05/29	四角形描画関数にテクスチャ情報を追加
//
//	2020/06/12	四角形描画関数に回転を追加
//
//	2020/06/25	頂点版四角形描画関数
//	
//	2020/07/22	スプライトクラスの作成
//
//===============================================

#pragma once

//====== インクルード部 ======
#include "main.h"
#include "texture.h"
#include "source/transform.h"
#include "shader.h"
#include "model.h"
#include "polygon.h"

//===== 構造体定義 =====
// 頂点情報
struct VERTEX_3D
{
	Float3 Position;	// 座標 x, y, z
	Float4 Color;		// 色   r, g, b, a
	Float2 TexCoord;	// テクスチャ情報
};

class CSprite
{
public:
	CSprite();
	~CSprite();

	static void Init();
	void Draw(CTransform* pTrans, CTexture *pTexture = nullptr);
	void Draw(CTransform *pTrans, CTexture *pTexture, bool bCamera);

	// セット関数
	void SetTexPos(Float2 texPos) { m_posTexCoord = texPos; }
	void SetTexSize(Float2 texSize) { m_sizeTexCoord = texSize; }
	void SetColor(Float4 color) { m_color = color; }
	void SetColorW(float w) { m_color.w = w; }
	//void SetTexture(CTexture *pTexture) { m_pTexture = pTexture; }

	// ゲット関数
	Float2 GetTexPos() { return m_posTexCoord; }
	Float2 GetTexSize() { return m_sizeTexCoord; }
	Float4 GetColor() { return m_color; }

private:
	Float2 m_posTexCoord;		// テクスチャ座標(左上)0.0～1.0
	Float2 m_sizeTexCoord;		// テクスチャサイズ(右下)0.0～1.0
	Float4 m_color;				// 頂点カラー

	// DirectX描画データ
	static CModel m_model;
	static CShader m_shader;
	static CPolygon m_polygon;
	static CTexture m_defaultTexture;
};
